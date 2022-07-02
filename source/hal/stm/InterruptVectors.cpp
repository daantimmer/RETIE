#include "hal/cortex/ExceptionHandlers.hpp"
#include <cstdint>

// Forward declaration of the specific IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
extern "C"
{
    void __attribute__((naked)) DefaultHandlerForward()
    {
        asm volatile("bx %0"
                     :
                     : "r"(Default_Handler));
    }

    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) WWDG_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) PVD_PVM_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) RTC_TAMP_LSECSS_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) RTC_WKUP_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FLASH_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) RCC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI0_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel6_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel7_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) ADC1_2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USB_HP_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USB_LP_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN1_IT0_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN1_IT1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI9_5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM1_BRK_TIM15_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM1_UP_TIM16_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM1_TRG_COM_TIM17_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM1_CC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C1_EV_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C1_ER_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C2_EV_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C2_ER_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) SPI1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) SPI2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USART1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USART2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USART3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) EXTI15_10_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) RTC_Alarm_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) USBWakeUp_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM8_BRK_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM8_UP_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM8_TRG_COM_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM8_CC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) ADC3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FMC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) LPTIM1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) SPI3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) UART4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) UART5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM6_DAC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM7_DAC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel2_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) ADC4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) ADC5_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) UCPD1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) COMP1_2_3_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) COMP4_5_6_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) COMP7_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_Master_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIMA_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIMB_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIMC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIMD_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIME_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_FLT_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) HRTIM1_TIMF_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) CRS_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) SAI1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM20_BRK_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM20_UP_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM20_TRG_COM_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) TIM20_CC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FPU_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C4_EV_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C4_ER_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) SPI4_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN2_IT0_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN2_IT1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN3_IT0_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FDCAN3_IT1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) RNG_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) LPUART1_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C3_EV_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) I2C3_ER_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMAMUX_OVR_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) QUADSPI_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA1_Channel8_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel6_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel7_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) DMA2_Channel8_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) CORDIC_IRQHandler();
    void __attribute__((weak, alias("DefaultHandlerForward"), nothrow)) FMAC_IRQHandler();

    // ----------------------------------------------------------------------------

    // extern unsigned int _estack;
    extern std::uint8_t _estack;

    using pHandler = void (*)();

    // ----------------------------------------------------------------------------

    // The vector table.
    // This relies on the linker script to place at correct location in memory.
    __attribute__((section(".isr_vector"), used)) pHandler g_pfnVectors[] = {
        reinterpret_cast<pHandler>(&_estack),
        Reset_Handler,
        NMI_Handler,
        HardFault_Handler,
        MemManage_Handler,
        BusFault_Handler,
        UsageFault_Handler,
        0,
        0,
        0,
        0,
        SVC_Handler,
        DebugMon_Handler,
        0,
        PendSV_Handler,
        SysTick_Handler,
        WWDG_IRQHandler,
        PVD_PVM_IRQHandler,
        RTC_TAMP_LSECSS_IRQHandler,
        RTC_WKUP_IRQHandler,
        FLASH_IRQHandler,
        RCC_IRQHandler,
        EXTI0_IRQHandler,
        EXTI1_IRQHandler,
        EXTI2_IRQHandler,
        EXTI3_IRQHandler,
        EXTI4_IRQHandler,
        DMA1_Channel1_IRQHandler,
        DMA1_Channel2_IRQHandler,
        DMA1_Channel3_IRQHandler,
        DMA1_Channel4_IRQHandler,
        DMA1_Channel5_IRQHandler,
        DMA1_Channel6_IRQHandler,
        DMA1_Channel7_IRQHandler,
        ADC1_2_IRQHandler,
        USB_HP_IRQHandler,
        USB_LP_IRQHandler,
        FDCAN1_IT0_IRQHandler,
        FDCAN1_IT1_IRQHandler,
        EXTI9_5_IRQHandler,
        TIM1_BRK_TIM15_IRQHandler,
        TIM1_UP_TIM16_IRQHandler,
        TIM1_TRG_COM_TIM17_IRQHandler,
        TIM1_CC_IRQHandler,
        TIM2_IRQHandler,
        TIM3_IRQHandler,
        TIM4_IRQHandler,
        I2C1_EV_IRQHandler,
        I2C1_ER_IRQHandler,
        I2C2_EV_IRQHandler,
        I2C2_ER_IRQHandler,
        SPI1_IRQHandler,
        SPI2_IRQHandler,
        USART1_IRQHandler,
        USART2_IRQHandler,
        USART3_IRQHandler,
        EXTI15_10_IRQHandler,
        RTC_Alarm_IRQHandler,
        USBWakeUp_IRQHandler,
        TIM8_BRK_IRQHandler,
        TIM8_UP_IRQHandler,
        TIM8_TRG_COM_IRQHandler,
        TIM8_CC_IRQHandler,
        ADC3_IRQHandler,
        FMC_IRQHandler,
        LPTIM1_IRQHandler,
        TIM5_IRQHandler,
        SPI3_IRQHandler,
        UART4_IRQHandler,
        UART5_IRQHandler,
        TIM6_DAC_IRQHandler,
        TIM7_DAC_IRQHandler,
        DMA2_Channel1_IRQHandler,
        DMA2_Channel2_IRQHandler,
        DMA2_Channel3_IRQHandler,
        DMA2_Channel4_IRQHandler,
        DMA2_Channel5_IRQHandler,
        ADC4_IRQHandler,
        ADC5_IRQHandler,
        UCPD1_IRQHandler,
        COMP1_2_3_IRQHandler,
        COMP4_5_6_IRQHandler,
        COMP7_IRQHandler,
        HRTIM1_Master_IRQHandler,
        HRTIM1_TIMA_IRQHandler,
        HRTIM1_TIMB_IRQHandler,
        HRTIM1_TIMC_IRQHandler,
        HRTIM1_TIMD_IRQHandler,
        HRTIM1_TIME_IRQHandler,
        HRTIM1_FLT_IRQHandler,
        HRTIM1_TIMF_IRQHandler,
        CRS_IRQHandler,
        SAI1_IRQHandler,
        TIM20_BRK_IRQHandler,
        TIM20_UP_IRQHandler,
        TIM20_TRG_COM_IRQHandler,
        TIM20_CC_IRQHandler,
        FPU_IRQHandler,
        I2C4_EV_IRQHandler,
        I2C4_ER_IRQHandler,
        SPI4_IRQHandler,
        0,
        FDCAN2_IT0_IRQHandler,
        FDCAN2_IT1_IRQHandler,
        FDCAN3_IT0_IRQHandler,
        FDCAN3_IT1_IRQHandler,
        RNG_IRQHandler,
        LPUART1_IRQHandler,
        I2C3_EV_IRQHandler,
        I2C3_ER_IRQHandler,
        DMAMUX_OVR_IRQHandler,
        QUADSPI_IRQHandler,
        DMA1_Channel8_IRQHandler,
        DMA2_Channel6_IRQHandler,
        DMA2_Channel7_IRQHandler,
        DMA2_Channel8_IRQHandler,
        CORDIC_IRQHandler,
        FMAC_IRQHandler,
    };
}