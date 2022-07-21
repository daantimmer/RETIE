#include "kernel/Scheduler.hpp"
#include "kernel/MainThread.hpp"
#include "kernel/ThreadControlBlock.hpp"
#include "kernel/arch/InterruptMasking.hpp"
#include "kernel/arch/RequestContextSwitch.hpp"

namespace kernel
{

    template <std::uint32_t (&Function)()>
    struct InterruptMaskingUnmaskingLock
    {
        ~InterruptMaskingUnmaskingLock()
        {
            arch::restoreInterruptMasking(interruptMask);
        }

        std::uint32_t interruptMask{Function()};
    };

    struct InterruptMaskingLock: InterruptMaskingUnmaskingLock<arch::enableInterruptMasking>
    {};

    void Scheduler::Add(ThreadControlBlock& tcb)
    {
        tcb.GetStack().Initialize(tcb.GetOwner());

        AddInternal(tcb);
    }

    void Scheduler::Add(MainThread& mt)
    {
        AddInternal(mt.GetThreadControlBlock());

        currentThreadControlBlock = &static_cast<ThreadControlBlock&>(readyList.top());
    }

    void Scheduler::Block()
    {
        Block(blockedList, GetCurrentThreadControlBlock());
    }

    void Scheduler::Block(ThreadList& threadList, ThreadControlBlock& tcb)
    {
        {
            const InterruptMaskingLock interruptMaskingLock;

            Transfer(tcb, threadList);
        }

        arch::RequestContextSwitch();
    }

    void Scheduler::Unblock(ThreadControlBlock& tcb)
    {
        const InterruptMaskingLock interruptMaskingLock;

        Transfer(tcb, readyList);

        RequestContextSwitchIfNeeded();
    }

    void Scheduler::Suspend()
    {
        Suspend(GetCurrentThreadControlBlock());
    }

    void Scheduler::Suspend(ThreadControlBlock& tcb)
    {
        Block(suspendedList, tcb);
    }

    void Scheduler::Resume(ThreadControlBlock& tcb)
    {
        const InterruptMaskingLock interruptMaskingLock;

        Unblock(tcb);
    }

    void Scheduler::Yield()
    {
        auto& tcb = GetCurrentThreadControlBlock();

        Transfer(tcb, readyList);

        RequestContextSwitchIfNeeded();
    }

    ThreadControlBlock& Scheduler::GetCurrentThreadControlBlock() const
    {
        return *currentThreadControlBlock;
    }

    void Scheduler::RequestContextSwitchIfNeeded()
    {
        if (IsContextSwitchRequired())
        {
            arch::RequestContextSwitch();
        }
    }

    void* Scheduler::SwitchContext(void* stackPointer)
    {
        auto& currentStack = GetCurrentThreadControlBlock().GetStack();
        currentStack.StackPointer(stackPointer);

        currentThreadControlBlock = static_cast<ThreadControlBlock*>(&readyList.top());

        if (currentThreadControlBlock == nullptr)
        {
            asm volatile("bkpt");
        }

        return GetCurrentThreadControlBlock().GetStack().StackPointer();
    }

    bool Scheduler::IsContextSwitchRequired() const
    {
        const auto isNotInReadyList = &GetCurrentThreadControlBlock().GetList() != &readyList;
        const auto isNotTopOfReadyList = &GetCurrentThreadControlBlock() != &readyList.top();

        return isNotInReadyList || isNotTopOfReadyList;
    }

    void Scheduler::AddInternal(ThreadControlBlock& tcb)
    {
        readyList.push(tcb);
        tcb.SetList(readyList);
        tcb.State(ThreadState::Ready);
    }

    void Scheduler::Transfer(ThreadControlBlock& tcb, ThreadList& threadList)
    {
        tcb.GetList().erase(tcb);
        threadList.push(tcb);
        tcb.SetList(threadList);
    }
}