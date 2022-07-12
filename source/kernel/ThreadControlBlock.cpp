#include "kernel/ThreadControlBlock.hpp"

namespace kernel
{

    ThreadControlBlockItem::ThreadControlBlockItem(std::uint8_t priority)
        : priority{priority}
    {}

    std::uint8_t ThreadControlBlockItem::GetPriority() const
    {
        return priority;
    }

    std::uint8_t ThreadControlBlockItem::GetEffectivePriority() const
    {
        return priorityInheritance == 0 ? GetPriority() : priorityInheritance;
    }

    bool ThreadControlBlockItem::operator>(const ThreadControlBlockItem& other) const
    {
        return GetEffectivePriority() > other.GetEffectivePriority();
    }

    // bool ThreadControlBlockItem::operator==(const ThreadControlBlockItem& other) const
    // {
    //     return GetEffectivePriority() == other.GetEffectivePriority();
    // }

    ThreadList& ThreadControlBlockItem::GetList() const
    {
        return *parentList;
    }

    void ThreadControlBlockItem::SetList(ThreadList& list)
    {
        parentList = &list;
    }

    ThreadControlBlock::ThreadControlBlock(std::uint8_t priority, Stack&& stack, IRunnableThread& owner)
        : ThreadControlBlockItem{priority}
        , stack{std::move(stack)}
        , owner{owner}
    {}

    ThreadState ThreadControlBlock::State() const
    {
        return state;
    }

    void ThreadControlBlock::State(ThreadState state)
    {
        this->state = state;
    }

    IRunnableThread& ThreadControlBlock::GetOwner() const
    {
        return owner;
    }

    Stack& ThreadControlBlock::GetStack()
    {
        return stack;
    }

    const Stack& ThreadControlBlock::GetStack() const
    {
        return stack;
    }
}