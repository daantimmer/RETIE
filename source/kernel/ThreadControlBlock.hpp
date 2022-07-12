#ifndef KERNEL_THREADCONTROLBLOCK_HPP
#define KERNEL_THREADCONTROLBLOCK_HPP

#include "infra/util/IntrusiveSet.hpp"
#include "kernel/Stack.hpp"
#include "kernel/ThreadList.hpp"

namespace kernel
{
    struct IRunnableThread;

    enum struct ThreadState
    {
        Created,
        Ready,
        Running,
        Blocked,
        Suspended
    };

    struct ThreadControlBlockItem: ThreadListNode
    {
        explicit ThreadControlBlockItem(std::uint8_t priority);

        std::uint8_t GetPriority() const;
        std::uint8_t GetEffectivePriority() const;

        bool operator>(const ThreadControlBlockItem& other) const;
        // bool operator==(const ThreadControlBlockItem& other) const;

        ThreadList& GetList() const;
        void SetList(ThreadList& list);

    private:
        std::uint8_t priority;
        std::uint8_t priorityInheritance{0};

        ThreadList* parentList;
    };

    struct ThreadControlBlock: ThreadControlBlockItem
    {
        explicit ThreadControlBlock(std::uint8_t priority, Stack&& stack, IRunnableThread& owner);

        ThreadState State() const;
        void State(ThreadState state);

        IRunnableThread& GetOwner() const;

        Stack& GetStack();
        const Stack& GetStack() const;

    private:
        Stack stack;

        ThreadState state;

        IRunnableThread& owner;
    };
}

#endif
