#include "hal/stm/SystemTick.hpp"

namespace
{
    volatile auto ticksDuringStartup = 0u;
}

namespace hal
{
    SystemTickStm::SystemTickStm(infra::Duration tickDuration, std::uint32_t id)
        : TickOnInterruptTimerService(id, tickDuration)
    {}

    void SystemTickStm::Elapsed()
    {
        SystemTickInterrupt();
    }
}

extern "C" void HAL_IncTick()
{
    if (hal::SystemTickStm::InstanceSet())
    {
        hal::SystemTickStm::Instance().Elapsed();
    }
    else
    {
        ++ticksDuringStartup;
    }
}

extern "C" std::uint32_t HAL_GetTick()
{
    if (hal::SystemTickStm::InstanceSet())
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   hal::SystemTickStm::Instance().Now().time_since_epoch())
            .count();
    }
    else
    {
        return ticksDuringStartup;
    }
}