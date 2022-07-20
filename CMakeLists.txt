cmake_minimum_required(VERSION 3.22.0)

project(powermock LANGUAGES C CXX VERSION 0.1.0)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(TARGET_BUILD_WIN On)
    set(TARGET_ARCH_X86 On)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(TARGET_BUILD_UNIX On)
    set(TARGET_ARCH_X86 On)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Generic")
    set(TARGET_ARCH_ARM On)

    enable_language(ASM)
    set(CMAKE_EXECUTABLE_SUFFIX .elf PARENT_SCOPE)
endif()

if (TARGET_ARCH_ARM)
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
endif()

include(FetchContent)
FetchContent_Declare(
    emil
    GIT_REPOSITORY https://github.com/philips-software/embeddedinfralib.git
    GIT_TAG        b76d00951b5b46aea8fde3408ba56275e633c933
    # GIT_TAG modern-cmake
)

FetchContent_MakeAvailable(emil)

if (TARGET_ARCH_ARM)
    add_subdirectory(source)
endif()