#ifndef KERNEL_THREAD_HPP
#define KERNEL_THREAD_HPP

#include "kernel/ThreadControlBlock.hpp"
#include <cstdint>

namespace kernel
{
    struct IThread
    {
        virtual ~IThread() = default;

        virtual ThreadState State() const = 0;
        virtual void State(ThreadState state) = 0;

        virtual std::size_t GetStackUsage() const = 0;
        virtual std::size_t GetStackSize() const = 0;

        virtual std::size_t GetPriority() const = 0;
        virtual std::size_t GetEffectivePriority() const = 0;
    };

    struct IRunnableThread: IThread
    {
        virtual ~IRunnableThread() = default;
        virtual void Run() = 0;
    };
}

#endif
