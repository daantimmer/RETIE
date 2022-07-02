#ifndef CORTEX_EXCEPTIONHANDLERS_HPP
#define CORTEX_EXCEPTIONHANDLERS_HPP

extern "C"
{
    void Default_Handler(void);

    void Reset_Handler(void);
    void NMI_Handler(void);
    void HardFault_Handler(void);
    void MemManage_Handler(void);
    void BusFault_Handler(void);
    void UsageFault_Handler(void);
    void SVC_Handler(void);
    void DebugMon_Handler(void);
    void PendSV_Handler(void);
    void SysTick_Handler(void);
}

#endif
