add_library(hal INTERFACE)

target_include_directories(hal INTERFACE
    ../
)

add_subdirectory(cortex)
add_subdirectory(stm)