add_library(hal.stm OBJECT)

target_sources(hal.stm PRIVATE
    InterruptVectors.cpp
    SystemTick.cpp
    SystemTick.hpp
    TicklessIrqTimer.hpp
    TicklessIrqTimerStm.cpp
    TicklessIrqTimerStm.hpp
    TicklessTimerSource.cpp
    TicklessTimerSource.hpp
)

target_link_libraries(hal.stm PUBLIC
    hal
    hal.cortex
    infra.event
    infra.util
    infra.timer

    stm32g474.cubemx
)

target_compile_features(hal.stm PUBLIC cxx_std_17)
