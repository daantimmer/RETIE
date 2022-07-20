#include "kernel/arch/InterruptMasking.hpp"
#include "device.hpp"
#include <cstdint>

namespace kernel::arch
{
    std::uint32_t disableInterruptMasking()
    {
        const auto interruptMask = __get_PRIMASK();
        __enable_irq();
        return interruptMask;
    }

    std::uint32_t enableInterruptMasking()
    {
        const auto interruptMask = __get_PRIMASK();
        __disable_irq();
        return interruptMask;
    }

    void restoreInterruptMasking(std::uint32_t interruptMask)
    {
        __set_PRIMASK(interruptMask);
    }
}
