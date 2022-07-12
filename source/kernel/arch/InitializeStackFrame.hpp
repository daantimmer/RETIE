#ifndef ARCH_INITIALIZESTACKFRAME_HPP
#define ARCH_INITIALIZESTACKFRAME_HPP

#include <cstdint>

namespace kernel
{
    struct IRunnableThread;
}

namespace kernel::arch
{
    void* InitializeStackFrame(void* const buffer, std::size_t size, kernel::IRunnableThread& thread);
}

#endif
