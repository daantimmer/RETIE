#ifndef SOURCE_EVENTDISPATCHERSTM_HPP
#define SOURCE_EVENTDISPATCHERSTM_HPP

#include "hal/stm/SystemTick.hpp"
#include "infra/event/EventDispatcher.hpp"

namespace hal
{
    struct EventDispatcherStm
    {
        EventDispatcherStm(infra::Duration tickDuration = std::chrono::milliseconds(1u));

        [[noreturn]] void Run();

    private:
        infra::EventDispatcher::WithSize<50> eventDispatcher;
        SystemTickStm systemTick;
    };
}

#endif
