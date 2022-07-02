add_library(hal.cortex.kernel INTERFACE)

target_link_libraries(hal.cortex.kernel INTERFACE
    hal.cortex
)

add_subdirectory(armv7)