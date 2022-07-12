#include "kernel/EventDispatcher.hpp"
#include "kernel/Scheduler.hpp"
#include "kernel/SchedulerInstance.hpp"

namespace kernel
{
    void EventDispatcherWorkerImpl::RequestExecution()
    {
        SchedulerInstance().Unblock(mainThread.GetThreadControlBlock());
    }

    void EventDispatcherWorkerImpl::Idle()
    {
        SchedulerInstance().Block();
    }
}