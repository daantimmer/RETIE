#include "kernel/ThreadBase.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/SchedulerInstance.hpp"

namespace kernel
{
    ThreadBase::ThreadBase(std::uint8_t priority, Stack&& stack)
        : threadControlBlock{priority, std::move(stack), *this}
    {}

    ThreadState ThreadBase::State() const
    {
        return GetThreadControlBlock().State();
    }

    void ThreadBase::State(ThreadState state)
    {
        GetThreadControlBlock().State(state);
    }

    std::size_t ThreadBase::GetStackUsage() const
    {
        return GetThreadControlBlock().GetStack().GetUsage();
    }

    std::size_t ThreadBase::GetStackSize() const
    {
        return GetThreadControlBlock().GetStack().GetSize();
    }

    std::size_t ThreadBase::GetPriority() const
    {
        return GetThreadControlBlock().GetPriority();
    }

    std::size_t ThreadBase::GetEffectivePriority() const
    {
        return GetThreadControlBlock().GetEffectivePriority();
    }

    ThreadControlBlock& ThreadBase::GetThreadControlBlock()
    {
        return threadControlBlock;
    }

    const ThreadControlBlock& ThreadBase::GetThreadControlBlock() const
    {
        return threadControlBlock;
    }

    void ThreadBase::Start()
    {
        SchedulerInstance().Add(GetThreadControlBlock());
    }
}
