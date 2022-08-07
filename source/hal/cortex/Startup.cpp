#include "hal/cortex/Startup.hpp"
#include "device.hpp"
#include <algorithm>
#include <cstdint>

extern "C"
{
    extern void __libc_init_array();
    extern void __libc_fini_array();

    extern void SystemInit();
    extern void SystemCoreClockUpdate();
    extern int main();

    extern unsigned int _sidata;
    extern unsigned int _sdata;
    extern unsigned int _edata;

    extern unsigned int _sbss;
    extern unsigned int _ebss;

    // extern unsigned int _siccmram;
    // extern unsigned int _sccmram;
    // extern unsigned int _eccmram;

    extern std::uint32_t __processStack_start[];
    extern std::uint32_t __processStack_end[];

    extern const char* __privelegedStack_end[];
}

namespace
{
    extern "C"
    {
        void SetUp()
        {
            std::copy(&_sidata, &_sidata + (&_edata - &_sdata), &_sdata);

            // std::copy(&_siccmram, &_siccmram + (&_eccmram - &_sccmram), &_sccmram);

            std::fill(&_sbss, &_ebss, 0);

            __libc_init_array();

            SystemInit();

            SystemCoreClockUpdate();

            DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM2_STOP | DBGMCU_APB1FZR1_DBG_TIM3_STOP
                | DBGMCU_APB1FZR1_DBG_TIM4_STOP | DBGMCU_APB1FZR1_DBG_TIM5_STOP | DBGMCU_APB1FZR1_DBG_TIM6_STOP
                | DBGMCU_APB1FZR1_DBG_TIM7_STOP;
        }

        [[noreturn]] void TearDown()
        {
            __libc_fini_array();

            while (true)
            {}
        }
    }
}

extern "C"
{
    [[noreturn]] __attribute__((section(".after_vectors"), naked)) void Startup()
    {
        asm volatile("ldr r0, =__processStack_end");
        asm volatile("msr psp, r0");
        asm volatile("movs r0, %[consrolSpselMask]" ::[consrolSpselMask] "i"(CONTROL_SPSEL_Msk));
        asm volatile("msr control, r0");
        asm volatile("isb");

        asm volatile("ldr r0, = SetUp");
        asm volatile("ldr r1, = 1");
        asm volatile("ldr r2, = 2");
        asm volatile("ldr r3, = 3");
        asm volatile("blx r0");

        asm volatile("ldr r0, = main");
        asm volatile("blx r0");

        asm volatile("ldr r0, = TearDown");
        asm volatile("blx r0");

        asm volatile("b .");
    }
}