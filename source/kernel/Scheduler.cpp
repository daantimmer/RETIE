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

        currentThreadControlBlock = &static_cast<ThreadControlBlock&>(readyList.front());
    }

    void Scheduler::Block()
    {
        {
            const InterruptMaskingLock interruptMaskingLock;

            auto& tcb = GetCurrentThreadControlBlock();
            tcb.GetList().erase(tcb);
            blockedList.push(tcb);
            tcb.SetList(blockedList);
        }

        arch::RequestContextSwitch();
    }

    void Scheduler::Unblock(ThreadControlBlock& tcb)
    {
        const InterruptMaskingLock interruptMaskingLock;

        tcb.GetList().erase(tcb);
        readyList.push(tcb);
        tcb.SetList(readyList);

        arch::RequestContextSwitch();
    }

    void Scheduler::Suspend(ThreadControlBlock& tcb)
    {
        tcb.GetList().erase(tcb);
        suspendedList.push(tcb);
        tcb.SetList(suspendedList);

        arch::RequestContextSwitch();
    }

    void Scheduler::Yield()
    {
        auto& tcb = GetCurrentThreadControlBlock();

        tcb.GetList().erase(tcb);
        readyList.push(tcb);
        tcb.SetList(readyList);

        arch::RequestContextSwitch();
    }

    ThreadControlBlock& Scheduler::GetCurrentThreadControlBlock() const
    {
        return *currentThreadControlBlock;
    }

    void* Scheduler::SwitchContext(void* stackPointer)
    {
        auto& currentStack = GetCurrentThreadControlBlock().GetStack();
        currentStack.StackPointer(stackPointer);

        currentThreadControlBlock = static_cast<ThreadControlBlock*>(&readyList.front());

        if (currentThreadControlBlock == nullptr)
        {
            asm volatile("bkpt");
        }

        return GetCurrentThreadControlBlock().GetStack().StackPointer();
    }

    void Scheduler::AddInternal(ThreadControlBlock& tcb)
    {
        readyList.push(tcb);
        tcb.SetList(readyList);
        tcb.State(ThreadState::Ready);
    }
}