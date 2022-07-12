#include "hal/cortex/kernel/arch/StackFrame.hpp"
#include <new>

namespace kernel::arch
{
    void* InitializeStackFrame(void* const buffer, std::size_t size, kernel::IRunnableThread& thread)
    {
        const auto stackFramePtr = reinterpret_cast<StackFrame*>(static_cast<std::uint8_t*>(buffer) + size) - 1;

        const auto stackFrame = new (stackFramePtr) StackFrame{};

        stackFrame->exceptionStackFrame.r0 = &thread;

        return stackFrame;
    }
}