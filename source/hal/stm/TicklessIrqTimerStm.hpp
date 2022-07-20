#ifndef STM_TICKLESSIRQTIMERSTM_HPP
#define STM_TICKLESSIRQTIMERSTM_HPP

#include "device.hpp"
#include "hal/cortex/Interrupt.hpp"
#include "hal/stm/TicklessIrqTimer.hpp"
#include "hal/stm/TicklessTimerSource.hpp"
#include "infra/util/AutoResetFunction.hpp"

namespace hal
{
    namespace details
    {

        struct TimHandle2Config
        {
            TIM_TypeDef& handle;
            uint8_t bus;
            IRQn_Type irqn;
        };
    }

    struct TicklessIrqTimerStm
        : hal::TicklessIrqTimer
        , hal::InterruptHandler
    {
    public:
        explicit TicklessIrqTimerStm(TIM_TypeDef& hardwareTimer, std::chrono::microseconds resolution);

        // TicklessIrqTimer
        void Compare(infra::TimePoint nextTrigger, std::size_t index, infra::Function<void()> action) override;
        void StopCompare(std::size_t index) override;

        infra::TimePoint Now() const override;

        // hal::InterruptHandler
        void Invoke() override;

    private:
        void HandleCaptureCompareInterrupt(std::size_t index);
        void HandleAction(std::size_t index);

        details::TimHandle2Config& config;

        std::uint32_t overflowTicks{0};

        std::array<infra::AutoResetFunction<void()>, 4> actions;
        std::array<infra::TimePoint, 4> nextTriggers;

        std::uint32_t overflowCount{0};
        infra::Duration resolution;
    };
}

#endif
