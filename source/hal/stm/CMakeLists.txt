add_library(hal.stm OBJECT)

target_sources(hal.stm PRIVATE
    EventDispatcher.cpp
    EventDispatcher.hpp
    InterruptVectors.cpp
    SystemTick.cpp
    SystemTick.hpp
)

target_link_libraries(hal.stm PUBLIC
    hal
    hal.cortex
    infra.event
    infra.util
    infra.timer
)