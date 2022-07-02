
add_library(hal.cortex OBJECT)

target_link_libraries(hal.cortex PUBLIC
    hal
    infra.util
    infra.event
)

target_sources(hal.cortex PRIVATE
    ExceptionHandlers.cpp
    ExceptionHandlers.hpp
    Interrupt.cpp
    Interrupt.hpp
    Startup.cpp
    Startup.hpp
)

add_subdirectory(kernel)