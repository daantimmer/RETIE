#include "kernel/MainThread.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/SchedulerInstance.hpp"

extern "C"
{
    extern std::uint32_t __processStack_start[]; // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    extern std::uint32_t __processStack_end[]; // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
}

namespace kernel
{

    MainThread::MainThread(std::uint8_t priority)
        : ThreadBase{priority,
                     Stack{StackUniquePtr{__processStack_start, [](void*) {}},
                           static_cast<std::size_t>((__processStack_end - __processStack_start)
                                                    * sizeof(__processStack_start[0]))}}
    {
        SchedulerInstance().Add(*this);
    }

    void MainThread::Run()
    {
        while (true)
        {
            asm volatile("bkpt");
        }
    }
}