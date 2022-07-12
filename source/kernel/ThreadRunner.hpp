#ifndef KERNEL_THREADRUNNER_HPP
#define KERNEL_THREADRUNNER_HPP

namespace kernel
{
    struct IRunnableThread;

    __attribute__((noreturn)) void ThreadRunner(IRunnableThread& runnableThread);
}

#endif
