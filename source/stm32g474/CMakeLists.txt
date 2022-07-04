add_subdirectory(cubemx)

target_link_libraries(hal.cortex PUBLIC
    stm32g474.cubemx
)

add_executable(stm32g474 main.cpp)

target_link_options(stm32g474 PRIVATE
    -specs=nano.specs
    -specs=nosys.specs 
    
    -Wl,--print-memory-usage
)

target_link_libraries(stm32g474 PRIVATE
    hal.cortex
    hal.cortex.kernel
    hal.cortex.kernel.armv7
    hal.stm
    stm32g474.cubemx
)