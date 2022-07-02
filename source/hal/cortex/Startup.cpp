#include "hal/cortex/Startup.hpp"

#include <algorithm>
#include <cstdint>

extern "C"
{
    extern void __libc_init_array(void);
    extern void SystemInit(void);
    extern int main(void);

    /*----------Symbols defined in linker script----------------------------------*/
    extern unsigned int _sidata;
    extern unsigned int _sdata;
    extern unsigned int _edata;

    extern unsigned int _sbss;
    extern unsigned int _ebss;

    // extern unsigned int _siccmram;
    // extern unsigned int _sccmram;
    // extern unsigned int _eccmram;

    [[noreturn]] void Startup(void)
    {
        std::copy(&_sidata, &_sidata + (&_edata - &_sdata), &_sdata);

        // std::copy(&_siccmram, &_siccmram + (&_eccmram - &_sccmram), &_sccmram);

        std::fill(&_sbss, &_ebss, 0);

        __libc_init_array();

        SystemInit();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        (void)main();
#pragma GCC diagnostic pop

        while (true)
        {
        }
    }
}