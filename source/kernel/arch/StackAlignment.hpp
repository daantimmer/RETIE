#ifndef ARCH_STACKALIGNMENT_HPP
#define ARCH_STACKALIGNMENT_HPP

#include <cstdint>

namespace kernel::arch
{
    void* AlignStackPointer(void* storage);

    std::size_t AdjustStackSize(void* original, void* storage, std::size_t size);
}

#endif
