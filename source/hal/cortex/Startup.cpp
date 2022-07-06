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
    [[noreturn]] void __attribute__((naked)) Startup()
    {
        asm volatile(
            R"(
                ldr r0, =__processStack_end
                msr psp, r0
                movs r0, %[consrolSpselMask]
                msr control, r0
                isb
            )"

            R"(
                ldr r0, = SetUp
                blx r0
            )"

            R"(
                ldr r0, = main
                blx r0
            )"

            R"(
                ldr r0, = TearDown
                blx r0
            )"

            R"(
                b .
            )" ::[consrolSpselMask] "i"(CONTROL_SPSEL_Msk));
    }
}