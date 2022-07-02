#include "hal/cortex/ExceptionHandlers.hpp"
#include "hal/cortex/Startup.hpp"
#include <stdlib.h>

extern "C"
{
    void __attribute__((section(".after_vectors"), weak, naked)) Reset_Handler(void)
    {
        asm volatile("ldr r0,=Startup");
        asm volatile("bx r0");
    }

    void __attribute__((weak)) Default_Handler()
    {
        abort();
    }

    void __attribute__((naked)) DefaultExceptionHandlerForward()
    {
        asm volatile("bx %0"
                     :
                     : "r"(Default_Handler));
    }

    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) NMI_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) HardFault_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) MemManage_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) BusFault_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) UsageFault_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) SVC_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) DebugMon_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) PendSV_Handler(void);
    void __attribute__((weak, alias("DefaultExceptionHandlerForward"), nothrow)) SysTick_Handler(void);
}