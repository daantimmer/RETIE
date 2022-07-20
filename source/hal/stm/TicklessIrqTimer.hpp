#ifndef STM_TICKLESSIRQTIMER_HPP
#define STM_TICKLESSIRQTIMER_HPP

#include "hal/stm/TicklessTimerSource.hpp"
#include "infra/event/EventDispatcher.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/Function.hpp"
#include <chrono>
#include <cstdint>

namespace hal
{
    struct TicklessIrqTimer
    {
        virtual void Compare(infra::TimePoint nextTrigger, std::size_t index, infra::Function<void()> action) = 0;
        virtual void StopCompare(std::size_t index) = 0;

        virtual infra::TimePoint Now() const = 0;
    };

    struct TicklessIrqTimerDispatchStrategy: infra::TicklessTimerSource
    {
        struct Immediate;
        struct Dispatched;

        TicklessIrqTimerDispatchStrategy(TicklessIrqTimer& ticklessIrqTimer,
                                         std::size_t channel,
                                         std::uint32_t id = infra::systemTimerServiceId,
                                         infra::Duration resolution = std::chrono::milliseconds(1u))
            : infra::TicklessTimerSource{id, resolution}
            , ticklessIrqTimer{ticklessIrqTimer}
            , channel{channel}
        {
            NextTriggerChanged();
        }

        infra::TimePoint Now() const override
        {
            return ticklessIrqTimer.Now();
        }

        void ClearNextTriggerPoint() override
        {
            ticklessIrqTimer.StopCompare(channel);
        }

    private:
        TicklessIrqTimer& ticklessIrqTimer;
        std::size_t channel;
    };

    struct TicklessIrqTimerDispatchStrategy::Immediate: TicklessIrqTimerDispatchStrategy
    {
        using TicklessIrqTimerDispatchStrategy::TicklessIrqTimerDispatchStrategy;

        void SetNextTriggerPoint(infra::TimePoint nextTrigger) override
        {
            ticklessIrqTimer.Compare(nextTrigger, channel, [this] {
                TimePointReached();
                NextTriggerChanged();
            });
        }
    };

    struct TicklessIrqTimerDispatchStrategy::Dispatched: TicklessIrqTimerDispatchStrategy
    {
        using TicklessIrqTimerDispatchStrategy::TicklessIrqTimerDispatchStrategy;

        void SetNextTriggerPoint(infra::TimePoint nextTrigger) override
        {
            ticklessIrqTimer.Compare(nextTrigger, channel, [this] {
                infra::EventDispatcher::Instance().Schedule([this] {
                    TimePointReached();
                    NextTriggerChanged();
                });
            });
        }
    };
}

#endif
