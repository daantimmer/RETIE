#include "main.h"
#include "hal/cortex/Interrupt.hpp"
#include "hal/stm/SystemTick.hpp"
#include "hal/stm/TicklessIrqTimerStm.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/IntrusiveSet.hpp"
#include "kernel/EventDispatcher.hpp"
#include "kernel/IdleThread.hpp"
#include "kernel/MainThread.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/StaticThread.hpp"
#include "kernel/arch/RequestContextSwitch.hpp"

extern "C" void Default_Handler()
{
    hal::InterruptTable::Instance().Invoke(hal::ActiveInterrupt());
}

extern "C" int RealMain()
{
    static hal::InterruptTable::WithStorage<128> interruptTable;
    static hal::TicklessIrqTimerStm timerIrqSource{*TIM2, std::chrono::microseconds{1}};
    static hal::TicklessIrqTimerDispatchStrategy::Dispatched ticklessSystemTimer{timerIrqSource,
                                                                                 0,
                                                                                 infra::systemTimerServiceId,
                                                                                 std::chrono::microseconds{1}};

    static infra::TimerRepeating timer;

    DBGMCU->CR |= DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP;

    static kernel::IdleThread idleThread{[]() {
        while (true)
        {
            asm volatile("wfe");
        }
    }};

    static kernel::EventDispatcher::WithSize<50> eventDispatcher;

    timer.Start(std::chrono::seconds{1}, []() { //
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    });

    eventDispatcher.Run();
    return 0;
}