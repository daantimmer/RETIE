#include "kernel/arch/StackAlignment.hpp"
#include "hal/cortex/kernel/arch/Configuration.hpp"
#include <cstdint>

namespace kernel::arch
{
    void* AlignStackPointer(void* storage)
    {
        const auto uintptr = reinterpret_cast<std::uintptr_t>(storage);
        const auto incremented = uintptr + stackAlignment - 1;
        const auto divided = incremented / stackAlignment;
        const auto multiplied = divided * stackAlignment;

        return reinterpret_cast<void*>(multiplied);
    }

    std::size_t AdjustStackSize(void* original, void* storage, std::size_t size)
    {
        const auto offset = reinterpret_cast<std::uint8_t*>(storage) - reinterpret_cast<std::uint8_t*>(original);
        const auto divided = (size - offset) / stackAlignment;
        const auto multiplied = divided * stackAlignment;

        return multiplied;
    }
}