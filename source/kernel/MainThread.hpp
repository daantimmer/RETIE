#ifndef KERNEL_MAINTHREAD_HPP
#define KERNEL_MAINTHREAD_HPP

#include "kernel/ThreadBase.hpp"

namespace kernel
{
    struct MainThread: ThreadBase
    {
        explicit MainThread(std::uint8_t priority = 1);

        void Run() override;
    };
}

#endif
