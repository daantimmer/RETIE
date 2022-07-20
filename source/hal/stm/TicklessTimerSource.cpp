#include "hal/stm/TicklessTimerSource.hpp"
#include "infra/event/EventDispatcher.hpp"
#include "infra/timer/TimerServiceManager.hpp"
#include <cassert>

namespace infra
{
    TicklessTimerSource::TicklessTimerSource(uint32_t id, Duration resolution)
        : TimerService(id)
        , resolution(resolution)
    {}

    void TicklessTimerSource::NextTriggerChanged()
    {
        const auto nextTrigger = NextTrigger();

        if (nextTrigger != infra::TimePoint::max())
        {
            const auto scaledTrigger = infra::Duration{(nextTrigger.time_since_epoch() / resolution) * resolution};

            SetNextTriggerPoint(infra::TimePoint(scaledTrigger));
        }
        else
        {
            ClearNextTriggerPoint();
        }
    }

    Duration TicklessTimerSource::Resolution() const
    {
        return resolution;
    }

    void TicklessTimerSource::SetResolution(Duration resolution)
    {
        this->resolution = resolution;
        NextTriggerChanged();
    }

    void TicklessTimerSource::TimePointReached()
    {
        Progressed(Now());
    }

    // void ImmediateTicklessInterruptService::TimePointReached()
    // {
    //     TicklessTimerSource::TimePointReached();
    //     NextTriggerChanged();
    // }

    // void DispatchedTicklessInterruptService::TimePointReached()
    // {
    //     infra::EventDispatcher::Instance().Schedule([this] {
    //         TicklessTimerSource::TimePointReached();
    //         NextTriggerChanged();
    //     });
    // }
}
