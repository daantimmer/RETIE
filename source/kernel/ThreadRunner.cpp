#include "kernel/ThreadRunner.hpp"
#include "kernel/Thread.hpp"

namespace kernel
{
    void ThreadRunner(IRunnableThread& runnableThread)
    {
        runnableThread.Run();

        __builtin_unreachable();
    }
}
