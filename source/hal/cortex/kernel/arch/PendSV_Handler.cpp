#include "device.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/SchedulerInstance.hpp"

namespace
{
    void* schedulerSwitchContextWrapper(void* const stack)
    {
        return kernel::SchedulerInstance().SwitchContext(stack);
    }

    constexpr auto RTOS_KERNEL_BASEPRI = 0;

    constexpr auto IsKernelPriorityHighest()
    {
        return RTOS_KERNEL_BASEPRI == 0;
    }

    constexpr auto GetBasePriorityRegisterValue()
    {
        constexpr auto priorityValue = RTOS_KERNEL_BASEPRI << (8 - __NVIC_PRIO_BITS);

        static_assert(IsKernelPriorityHighest() || (priorityValue > 0 && priorityValue <= UINT8_MAX));

        return priorityValue;
    }

    constexpr auto IsArmV6()
    {
        return __CORTEX_M < 4;
    }

    constexpr auto IsFpuEnabled()
    {
        return __FPU_PRESENT == 1 && __FPU_USED == 1;
    }

}

extern "C" __attribute__((naked)) void PendSV_Handler()
{
    if constexpr (IsKernelPriorityHighest())
    {
        asm volatile("cpsid i");
    }
    else
    {
        asm volatile("mov r0, %[basePriority]" ::[basePriority] "i"(GetBasePriorityRegisterValue));
        asm volatile("msr basepri, r0");
    }

    if constexpr (IsArmV6())
    {}
    else
    {
        asm volatile("mrs r0, psp");

        if constexpr (IsFpuEnabled())
        {
            asm volatile("tst lr, #1 << 4");
            asm volatile("it eq");
            asm volatile("vstmdbeq r0!, {s16-s31}");

            asm volatile("stmdb r0!, {r4-r12, lr}");
        }
        else
        {
            asm volatile("stmdb r0!, {r4-r11}");
            asm volatile("mov r4, lr");
        }

        asm volatile("bl %[schedulerSwitchContext]" ::[schedulerSwitchContext] "i"(schedulerSwitchContextWrapper));

        if constexpr (IsFpuEnabled())
        {
            asm volatile("ldmia r0!, {r4-r12, lr}");
            asm volatile("tst lr, #1 << 4");
            asm volatile("it eq");
            asm volatile("vldmiaeq r0!, {s16-s31}");
        }
        else
        {
            asm volatile("mov lr, r4");
            asm volatile("ldmia r0!, {r4-r11}");
        }

        asm volatile("msr psp, r0");
    }

    if constexpr (IsKernelPriorityHighest())
    {
        asm volatile("cpsie i");
    }
    else
    {
        asm volatile("mov r0, #0");
        asm volatile("msr basepri, r0");
    }

    asm volatile("bx lr");
    asm volatile(".ltorg");
}