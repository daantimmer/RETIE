#ifndef KERNEL_EVENTDISPATCHER_HPP
#define KERNEL_EVENTDISPATCHER_HPP

#include "infra/event/EventDispatcher.hpp"
#include "kernel/MainThread.hpp"

namespace kernel
{
    struct EventDispatcherWorkerImpl: infra::EventDispatcherWorkerImpl
    {
        using infra::EventDispatcherWorkerImpl::EventDispatcherWorkerImpl;

    protected:
        void RequestExecution() override;
        void Idle() override;

    private:
        MainThread mainThread;
    };

    using EventDispatcher = infra::EventDispatcherConnector<EventDispatcherWorkerImpl>;
}

#endif
