#ifndef ARMV7_STACKFRAME_HPP
#define ARMV7_STACKFRAME_HPP

#include "device.hpp"
#include <cstdint>

namespace hal::kernel
{
    using wr = void*;

    struct SoftwareStackFrame
    {
        static constexpr std::uintptr_t exceptionReturnDefaultValue{0xFF'FF'FF'FD};

#if __CORTEX_M == 4
        void* r4{reinterpret_cast<void*>(0x44444444)};
        void* r5{reinterpret_cast<void*>(0x55555555)};
        void* r6{reinterpret_cast<void*>(0x66666666)};
        void* r7{reinterpret_cast<void*>(0x77777777)};
#endif

        void* r8{reinterpret_cast<void*>(0x88888888)};
        void* r9{reinterpret_cast<void*>(0x99999999)};
        void* r10{reinterpret_cast<void*>(0xAAAAAAAA)};
        void* r11{reinterpret_cast<void*>(0xBBBBBBBB)};

#if __CORTEX_M != 4
        void* r4{reinterpret_cast<void*>(0x44444444)};
        void* r5{reinterpret_cast<void*>(0x55555555)};
        void* r6{reinterpret_cast<void*>(0x66666666)};
        void* r7{reinterpret_cast<void*>(0x77777777)};
#endif

#if __FPU_PRESENT == 1 && __FPU_USED == 1
        void* reserved{0};
        void* exceptionReturn{reinterpret_cast<void*>(exceptionReturnDefaultValue)};
#endif
    };

    struct ExceptionStackFrame
    {
        static constexpr std::uintptr_t xpsrDefaultValue{0x01'00'00'00};

        void* r0{reinterpret_cast<void*>(0x00000000)};
        void* r1{reinterpret_cast<void*>(0x11111111)};
        void* r2{reinterpret_cast<void*>(0x22222222)};
        void* r3{reinterpret_cast<void*>(0x33333333)};

        void* r12{reinterpret_cast<void*>(0xCCCCCCCC)};
        void* lr{nullptr};
        void* pc{nullptr};
        void* xpsr{reinterpret_cast<void*>(xpsrDefaultValue)};
    };

    struct StackFrame
    {
        SoftwareStackFrame softwareStackFrame;
        ExceptionStackFrame exceptionStackFrame;
    };

    void* InitializeStackFrame(void* const buffer, std::size_t size, void* obj);
}

#endif
