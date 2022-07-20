#include "hal/stm/TicklessIrqTimerStm.hpp"
#include "device.hpp"
#include "device_hal.hpp"
#include "hal/cortex/Interrupt.hpp"
#include <chrono>
#include <limits>

namespace hal
{
    namespace
    {

        std::array<details::TimHandle2Config, 4> mappingConfig{{
            {*TIM2, 1, IRQn_Type::TIM2_IRQn},
            {*TIM3, 1, IRQn_Type::TIM3_IRQn},
            {*TIM4, 1, IRQn_Type::TIM4_IRQn},
            {*TIM5, 1, IRQn_Type::TIM5_IRQn},
        }};

        details::TimHandle2Config& MapHandle2Config(TIM_TypeDef& handle)
        {
            for (auto& m : mappingConfig)
                if (&m.handle == &handle)
                    return m;

            __builtin_unreachable();
        }

        void StartCaptureCompare(TIM_TypeDef& handle, std::size_t index, std::uint32_t offset)
        {
            const auto CCRx = offset;

            switch (index)
            {
                default:
                case 0:
                    handle.CCR1 = CCRx;

                    handle.CCER |= TIM_CCER_CC1E;
                    handle.EGR = TIM_EGR_CC1G;
                    handle.SR = ~TIM_SR_CC1IF;
                    handle.DIER |= TIM_DIER_CC1IE;
                    break;
                case 1:
                    handle.CCR2 = CCRx;

                    handle.CCER |= TIM_CCER_CC2E;
                    handle.EGR = TIM_EGR_CC2G;
                    handle.SR = ~TIM_SR_CC2IF;
                    handle.DIER |= TIM_DIER_CC2IE;
                    break;
                case 2:
                    handle.CCR3 = CCRx;

                    handle.CCER |= TIM_CCER_CC3E;
                    handle.EGR = TIM_EGR_CC3G;
                    handle.SR = ~TIM_SR_CC3IF;
                    handle.DIER |= TIM_DIER_CC3IE;
                    break;
                case 3:
                    handle.CCR4 = CCRx;

                    handle.CCER |= TIM_CCER_CC4E;
                    handle.EGR = TIM_EGR_CC4G;
                    handle.SR = ~TIM_SR_CC4IF;
                    handle.DIER |= TIM_DIER_CC4IE;
                    break;
            }
        }

        void StartCaptureCompare(TIM_TypeDef& handle,
                                 std::size_t index,
                                 infra::TimePoint timePoint,
                                 infra::Duration resolution)
        {
            const auto timeSinceEpoch = timePoint.time_since_epoch();
            const auto scaledTimeSinceEpoch = timeSinceEpoch / resolution;

            const auto countsNextTrigger = scaledTimeSinceEpoch % handle.ARR;

            StartCaptureCompare(handle, index, countsNextTrigger);
        }

        constexpr void StopCaptureCompare(TIM_TypeDef& handle, std::size_t index)
        {
            switch (index)
            {
                default:
                case 0:
                    handle.CCER &= ~TIM_CCER_CC1E;
                    handle.DIER &= ~TIM_DIER_CC1IE;
                    handle.SR = ~TIM_SR_CC1IF;
                    break;
                case 1:
                    handle.CCER &= ~TIM_CCER_CC2E;
                    handle.DIER &= ~TIM_DIER_CC2IE;
                    handle.SR = ~TIM_SR_CC2IF;
                    break;
                case 2:
                    handle.CCER &= ~TIM_CCER_CC3E;
                    handle.DIER &= ~TIM_DIER_CC3IE;
                    handle.SR = ~TIM_SR_CC3IF;
                    break;
                case 3:
                    handle.CCER &= ~TIM_CCER_CC4E;
                    handle.DIER &= ~TIM_DIER_CC4IE;
                    handle.SR = ~TIM_SR_CC4IF;
                    break;
            }
        }

        constexpr void TriggerCaptureCompareInterrupt(TIM_TypeDef& handle, std::size_t index)
        {
            switch (index)
            {
                default:
                case 0:
                    handle.EGR = TIM_EGR_CC1G;
                    break;
                case 1:
                    handle.EGR = TIM_EGR_CC2G;
                    break;
                case 2:
                    handle.EGR = TIM_EGR_CC3G;
                    break;
                case 3:
                    handle.EGR = TIM_EGR_CC4G;
                    break;
            }
        }

        constexpr bool IsInterruptActive(TIM_TypeDef& handle, std::size_t index)
        {
            switch (index)
            {
                default:
                case 0:
                    return handle.SR & TIM_SR_CC1IF && handle.DIER & TIM_DIER_CC1IE;
                case 1:
                    return handle.SR & TIM_SR_CC2IF && handle.DIER & TIM_DIER_CC2IE;
                case 2:
                    return handle.SR & TIM_SR_CC3IF && handle.DIER & TIM_DIER_CC3IE;
                case 3:
                    return handle.SR & TIM_SR_CC4IF && handle.DIER & TIM_DIER_CC4IE;
            }
        }

        constexpr void ClearInterrupt(TIM_TypeDef& handle, std::size_t index)
        {
            switch (index)
            {
                default:
                case 0:
                    handle.SR = ~TIM_SR_CC1IF;
                    break;
                case 1:
                    handle.SR = ~TIM_SR_CC2IF;
                    break;
                case 2:
                    handle.SR = ~TIM_SR_CC3IF;
                    break;
                case 3:
                    handle.SR = ~TIM_SR_CC4IF;
                    break;
            }
        }

        constexpr bool IsCaptureCompareActive(TIM_TypeDef& handle, std::size_t index)
        {
            switch (index)
            {
                default:
                case 0:
                    return (handle.CCMR1 & TIM_CCMR1_CC1S) == 0;
                case 1:
                    return (handle.CCMR1 & TIM_CCMR1_CC2S) == 0;
                case 2:
                    return (handle.CCMR2 & TIM_CCMR2_CC3S) == 0;
                case 3:
                    return (handle.CCMR2 & TIM_CCMR2_CC4S) == 0;
            }
        }

        std::uint32_t GetTimerClockFrequency(std::uint8_t apbBus)
        {
            if (apbBus == 1)
            {
                const auto timerInputFreq = HAL_RCC_GetPCLK1Freq();
                // determine if the prescaler is set, if so the APB1 frequency is multiplied by two
                if ((RCC->CFGR & RCC_CFGR_PPRE1) != 0)
                {
                    return timerInputFreq * 2;
                }
                return timerInputFreq;
            }
            else if (apbBus == 2)
            {
                const auto timerInputFreq = HAL_RCC_GetPCLK2Freq();
                // determine if the prescaler is set, if so the APB1 frequency is multiplied by two
                if ((RCC->CFGR & RCC_CFGR_PPRE2) != 0)
                {
                    return timerInputFreq * 2;
                }
                return timerInputFreq;
            }
            else
            {
                return 0;
            }
        }
    }

    TicklessIrqTimerStm::TicklessIrqTimerStm(TIM_TypeDef& hardwareTimer, std::chrono::microseconds resolution)
        : config(MapHandle2Config(hardwareTimer))
        , resolution{resolution}
    {
        // get frequency for the APBxtimer clock
        const auto timerInputFreq = GetTimerClockFrequency(config.bus);

        // setup prescaler to tick every microsecond
        const auto clocksPerMicroSecond = timerInputFreq / 1'000'000u;

        // minus one as the prescaler counts and counter from zero
        config.handle.PSC = (clocksPerMicroSecond * resolution.count()) - 1;
        // config.handle.ARR = std::numeric_limits<std::uint32_t>::max();
        config.handle.ARR = 999'999;
        config.handle.CNT = 0;

        Register(config.irqn);

        // start the timer
        config.handle.EGR = TIM_EGR_UG | TIM_EGR_CC1G | TIM_EGR_CC2G | TIM_EGR_CC3G | TIM_EGR_CC4G;
        config.handle.SR = ~(TIM_SR_UIF | TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF | TIM_SR_CC4IF);

        config.handle.DIER |= TIM_DIER_UIE;
        config.handle.CR1 |= TIM_CR1_CEN;
    }

    void TicklessIrqTimerStm::Compare(infra::TimePoint nextTrigger, std::size_t index, infra::Function<void()> action)
    {
        ScopedInterruptDisable irqDisable{config.irqn};

        StopCompare(index);

        actions[index] = action;
        nextTriggers[index] = nextTrigger;

        StartCaptureCompare(config.handle, index, nextTrigger, resolution);

        if (const auto now = Now(); now > nextTriggers[index])
        {
            TriggerCaptureCompareInterrupt(config.handle, index);
        }
    }

    void TicklessIrqTimerStm::StopCompare(std::size_t index)
    {
        StopCaptureCompare(config.handle, index);
    }

    infra::TimePoint TicklessIrqTimerStm::Now() const
    {
        ScopedInterruptDisable irqDisable{config.irqn};

        const auto localCnt = config.handle.CNT;
        const auto isIsrPending = static_cast<bool>(config.handle.SR & TIM_SR_UIF);
        const auto localCntOverflowCorrected = isIsrPending ? config.handle.CNT : localCnt;
        const auto correctedOverflowCountValue = overflowCount + (isIsrPending ? 1 : 0);

        const infra::TimePoint systemTime{(static_cast<std::uint64_t>(config.handle.ARR) + 1)
                                          * correctedOverflowCountValue * resolution};

        return systemTime + (localCntOverflowCorrected * resolution);
    }

    void TicklessIrqTimerStm::Invoke()
    {
        if (config.handle.SR & TIM_SR_UIF && config.handle.DIER & TIM_DIER_UIE)
        {
            config.handle.SR = ~TIM_SR_UIF;

            ++overflowCount;
        }

        HandleCaptureCompareInterrupt(0);

        HandleCaptureCompareInterrupt(1);

        HandleCaptureCompareInterrupt(2);

        HandleCaptureCompareInterrupt(3);
    }

    void TicklessIrqTimerStm::HandleCaptureCompareInterrupt(std::size_t index)
    {
        if (IsInterruptActive(config.handle, index))
        {
            ClearInterrupt(config.handle, index);

            const auto now = Now();

            if (IsCaptureCompareActive(config.handle, index) && (now >= nextTriggers[index]))
            {
                HandleAction(index);
            }
        }
    }

    void TicklessIrqTimerStm::HandleAction(std::size_t index)
    {
        StopCompare(index);
        nextTriggers[index] = infra::TimePoint::max();

        if (actions[index])
        {
            actions[index]();
        }
    }
}