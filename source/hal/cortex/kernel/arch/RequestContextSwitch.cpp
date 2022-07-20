#include "kernel/arch/RequestContextSwitch.hpp"
#include "device.hpp"

namespace kernel::arch
{
    void RequestContextSwitch()
    {
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
        __ISB();
    }
}