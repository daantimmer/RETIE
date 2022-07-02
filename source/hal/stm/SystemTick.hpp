#ifndef SOURCE_SYSTEMTICK_HPP
#define SOURCE_SYSTEMTICK_HPP

#include "infra/timer/TickOnInterruptTimerService.hpp"
#include "infra/util/InterfaceConnector.hpp"
#include <cstdint>

namespace hal
{
    struct SystemTickStm
        : infra::InterfaceConnector<SystemTickStm>
        , infra::TickOnInterruptTimerService
    {
        SystemTickStm(infra::Duration tickDuration = std::chrono::milliseconds(1u),
                      std::uint32_t id = infra::systemTimerServiceId);

        void Elapsed();
    };
}

#endif
