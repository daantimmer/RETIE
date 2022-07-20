#ifndef ARCH_INTERRUPTMASKING_HPP
#define ARCH_INTERRUPTMASKING_HPP

#include <cstdint>

namespace kernel::arch
{
    std::uint32_t disableInterruptMasking();
    std::uint32_t enableInterruptMasking();

    void restoreInterruptMasking(std::uint32_t interruptMask);
}

#endif
