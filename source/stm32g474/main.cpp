#include "hal/stm/EventDispatcher.hpp"

extern "C" int RealMain()
{
    static hal::EventDispatcherStm eventDispatcher;

    eventDispatcher.Run();
    return 0;
}