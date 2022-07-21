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
        void Block(ThreadList& threadList, ThreadControlBlock& tcb);
        void Unblock(ThreadControlBlock& tcb);

        void Suspend();
        void Suspend(ThreadControlBlock& tcb);
        void Resume(ThreadControlBlock& tcb);

        void Yield();

        ThreadControlBlock& GetCurrentThreadControlBlock() const;

        void RequestContextSwitchIfNeeded();

        void* SwitchContext(void* stackPointer);

    private:
        bool IsContextSwitchRequired() const;

        void AddInternal(ThreadControlBlock& tcb);
        void Transfer(ThreadControlBlock& tcb, ThreadList& threadList);

        ThreadList readyList;
        ThreadList blockedList;
        ThreadList suspendedList;

        ThreadControlBlock* currentThreadControlBlock{nullptr};
    };
}

#endif
