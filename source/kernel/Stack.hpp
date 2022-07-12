#ifndef KERNEL_STACK_HPP
#define KERNEL_STACK_HPP

#include <memory>

namespace kernel
{
    struct IRunnableThread;

    using StackUniquePtr = std::unique_ptr<void, void (*)(void*)>;

    struct Stack
    {
        Stack(StackUniquePtr&& storageOwner, std::size_t size);

        std::size_t GetUsage() const;
        std::size_t GetSize() const;

        void* StackPointer() const;
        void StackPointer(void*);

        void Initialize(IRunnableThread& runnableThread);

    private:
        StackUniquePtr storageOwner;

        void* storage{nullptr};
        std::size_t size{0};

        void* stackPointer{nullptr};
    };
}

#endif
