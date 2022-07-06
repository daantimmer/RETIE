#include "hal/cortex/kernel/armv7/StackFrame.hpp"
#include <new>

namespace hal::kernel
{
    void* InitializeStackFrame(void* const buffer, std::size_t size, void* obj)
    {
        const auto stackFramePtr = reinterpret_cast<StackFrame*>(static_cast<std::uint8_t*>(buffer) + size) - 1;

        const auto stackFrame = new (stackFramePtr) StackFrame{};

        stackFrame->exceptionStackFrame.r0 = obj;

        stackFrame->exceptionStackFrame.lr = nullptr;
        stackFrame->exceptionStackFrame.pc = nullptr;

        return stackFrame;
    }
}