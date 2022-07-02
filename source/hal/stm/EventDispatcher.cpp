#include "hal/stm/EventDispatcher.hpp"

namespace hal
{
    EventDispatcherStm::EventDispatcherStm(infra::Duration tickDuration)
        : systemTick{tickDuration}
    {}

    void EventDispatcherStm::Run()
    {
        eventDispatcher.Run();

        __builtin_unreachable();
    }
}
