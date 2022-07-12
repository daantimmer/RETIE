#ifndef KERNEL_CONFIGURATION_HPP
#define KERNEL_CONFIGURATION_HPP

namespace kernel
{
    static constexpr auto stackSentinel = 0x7C290637u;

    static constexpr auto idleThreadStackSize = 1024u;
}

#endif
