#ifndef STM_TICKLESSTIMERSOURCE_HPP
#define STM_TICKLESSTIMERSOURCE_HPP

#include "infra/timer/TimerService.hpp"
#include <atomic>

namespace infra
{
    struct TicklessTimerSource: TimerService
    {
        TicklessTimerSource(std::uint32_t id = infra::systemTimerServiceId,
                            infra::Duration resolution = std::chrono::milliseconds(1u));

        virtual void NextTriggerChanged() override;
        virtual Duration Resolution() const override;

        void SetResolution(Duration resolution);

    protected:
        virtual void SetNextTriggerPoint(infra::TimePoint nextTrigger) = 0;
        virtual void ClearNextTriggerPoint() = 0;

        virtual void TimePointReached();

    private:
        void ProcessTicks();

    private:
        Duration resolution;
    };
}

#endif
