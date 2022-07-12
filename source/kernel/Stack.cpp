#include "kernel/Stack.hpp"
#include "kernel/Configuration.hpp"
#include "kernel/arch/InitializeStackFrame.hpp"
#include "kernel/arch/StackAlignment.hpp"

namespace kernel
{

    Stack::Stack(StackUniquePtr&& storageOwner, std::size_t size)
        : storageOwner{std::move(storageOwner)}
        , storage{arch::AlignStackPointer(this->storageOwner.get())}
        , size{arch::AdjustStackSize(this->storageOwner.get(), storage, size)}
    {}

    std::size_t Stack::GetUsage() const
    {
        return 0;
    }

    std::size_t Stack::GetSize() const
    {
        return size;
    }

    void* Stack::StackPointer() const
    {
        return stackPointer;
    }

    void Stack::StackPointer(void* stackPointer)
    {
        this->stackPointer = stackPointer;
    }

    void Stack::Initialize(IRunnableThread& runnableThread)
    {
        std::fill_n(reinterpret_cast<std::decay_t<decltype(stackSentinel)>*>(storage),
                    GetSize() / sizeof(decltype(stackSentinel)),
                    stackSentinel);
        stackPointer = arch::InitializeStackFrame(storage, GetSize(), runnableThread);
    }

}
