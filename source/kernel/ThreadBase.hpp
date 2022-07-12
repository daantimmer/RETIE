#ifndef KERNEL_THREADBASE_HPP
#define KERNEL_THREADBASE_HPP

#include "kernel/Stack.hpp"
#include "kernel/Thread.hpp"
#include "kernel/ThreadControlBlock.hpp"
#include <cstdint>

namespace kernel
{
    struct ThreadBase: IRunnableThread
    {
        ThreadBase(std::uint8_t priority, Stack&& stack);
        ~ThreadBase() = default;

        // IThread
        ThreadState State() const override;
        void State(ThreadState state) override;

        std::size_t GetStackUsage() const override;
        std::size_t GetStackSize() const override;

        std::size_t GetPriority() const override;
        std::size_t GetEffectivePriority() const override;

        // ThreadBase
        ThreadControlBlock& GetThreadControlBlock();
        const ThreadControlBlock& GetThreadControlBlock() const;

    protected:
        void Start();

    private:
        ThreadControlBlock threadControlBlock;
    };
}

#endif
