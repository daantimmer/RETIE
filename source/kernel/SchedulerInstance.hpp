#ifndef KERNEL_SCHEDULERINSTANCE_HPP
#define KERNEL_SCHEDULERINSTANCE_HPP

namespace kernel
{
    struct Scheduler;

    inline Scheduler& SchedulerInstance()
    {
        extern Scheduler schedulerInstance;
        return schedulerInstance;
    }
}

#endif
