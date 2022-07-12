#include "hal/stm/SystemTick.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/IntrusiveSet.hpp"
#include "kernel/EventDispatcher.hpp"
#include "kernel/IdleThread.hpp"
#include "kernel/MainThread.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/StaticThread.hpp"
#include "kernel/arch/RequestContextSwitch.hpp"

extern "C" int RealMain()
{
    static hal::SystemTickStm systemTick;

    static kernel::IdleThread idleThread{[]() {
        while (true)
        {
            asm volatile("wfe");
        }
    }};

    static kernel::EventDispatcher::WithSize<50> eventDispatcher;

    eventDispatcher.Run();
    return 0;
}