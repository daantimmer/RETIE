#ifndef KERNEL_IDLETHREAD_HPP
#define KERNEL_IDLETHREAD_HPP

#include "kernel/Configuration.hpp"
#include "kernel/StaticThread.hpp"

namespace kernel
{
    struct IdleThread: StaticThread<idleThreadStackSize>
    {
        IdleThread(infra::Function<void()> entry)
            : StaticThread{0, entry}
        {}
    };
}

#endif
