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
    hal.stm
    kernel
    stm32g474.cubemx
)

add_custom_command(
    TARGET stm32g474
    POST_BUILD 
    COMMAND ${ARM_OBJ_DUMP_TOOL} -h -S "$<TARGET_FILE:stm32g474>" > "$<TARGET_FILE:stm32g474>.lst"
    COMMAND ${ARM_OBJ_COPY_TOOL} -O binary "$<TARGET_FILE:stm32g474>" "$<TARGET_FILE:stm32g474>.bin"
    COMMAND ${ARM_OBJ_COPY_TOOL} -O ihex "$<TARGET_FILE:stm32g474>" "$<TARGET_FILE:stm32g474>.hex"
)