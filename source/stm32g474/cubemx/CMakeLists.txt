set(BOARD_LINKER_FILE ${CMAKE_CURRENT_LIST_DIR}/STM32G474RETx_FLASH.ld)

set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY CMAKE_CONFIGURE_DEPENDS KiTestControl.ioc)

file(GLOB_RECURSE SOURCES *.c *.h)

add_library(stm32g474.cubemx OBJECT)

target_include_directories(stm32g474.cubemx SYSTEM
    PUBLIC
        .
        Core/Inc
        Drivers/CMSIS/Device/ST/STM32G4xx/Include
        Drivers/CMSIS/Include
        Drivers/STM32G4xx_HAL_Driver/Inc
)

target_compile_definitions(stm32g474.cubemx PUBLIC
    STM32G474xx
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER
)

target_sources(stm32g474.cubemx PRIVATE
    ${SOURCES}

    device_hal.hpp
    device.hpp
)

target_link_options(stm32g474.cubemx PUBLIC
    -Wl,-Map=${PROJECT_NAME}.map
    -T${BOARD_LINKER_FILE}
)