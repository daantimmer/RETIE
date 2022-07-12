#ifndef KERNEL_SCHEDULER_HPP
#define KERNEL_SCHEDULER_HPP

#include "kernel/ThreadList.hpp"

namespace kernel
{
    struct ThreadControlBlock;
    struct MainThread;

    struct Scheduler
    {
        void Add(ThreadControlBlock& tcb);
        void Add(MainThread& mt);

        void Block();
        void Unblock(ThreadControlBlock& tcb);

        void Suspend(ThreadControlBlock& tcb);

        void Yield();

        ThreadControlBlock& GetCurrentThreadControlBlock() const;

        void* SwitchContext(void* stackPointer);

    private:
        void AddInternal(ThreadControlBlock& tcb);

        ThreadList readyList;
        ThreadList suspendedList;

        ThreadControlBlock* currentThreadControlBlock{nullptr};
    };
}

#endif
