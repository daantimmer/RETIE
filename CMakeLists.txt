cmake_minimum_required(VERSION 3.22.0)

project(powermock VERSION 0.1.0)


add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter

    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard

    -g3
    -ggdb
    -ffunction-sections
    -fdata-sections
    
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
)

add_link_options(
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    
    -specs=nano.specs
    -specs=nosys.specs 

    -g3
    -ggdb
    -ffunction-sections
    -fdata-sections

    -Wl,--print-memory-usage
    -Wl,--gc-sections 

    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
)


include(FetchContent)
FetchContent_Declare(
    emil
    GIT_REPOSITORY https://github.com/philips-software/embeddedinfralib.git
    # GIT_TAG        9d5a3e99f8389d3047cfe27901fffbc6373e02df
    GIT_TAG modern-cmake
)

FetchContent_MakeAvailable(emil)

add_subdirectory(source)