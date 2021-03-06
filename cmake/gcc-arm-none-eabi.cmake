set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(hints_paths)

if(CMAKE_HOST_WIN32)
    set(X86_PROGRAM_FILES "ProgramFiles(x86)")
    list(APPEND hints_paths "$ENV{${X86_PROGRAM_FILES}}/GNU Arm Embedded Toolchain/10 2021.07/bin")
endif()

find_program(CMAKE_C_COMPILER
    NAMES arm-none-eabi-gcc
    HINTS ${hints_paths})

find_program(CMAKE_CXX_COMPILER
    NAMES arm-none-eabi-g++
    HINTS ${hints_paths})

find_program(CMAKE_ASM_COMPILER
    NAMES arm-none-eabi-g++
    HINTS ${hints_paths})

find_program(CMAKE_AR
    NAMES arm-none-eabi-ar
    HINTS ${hints_paths})

find_program(CMAKE_RANLIB
    NAMES arm-none-eabi-ranlib
    HINTS ${hints_paths})

find_program(CMAKE_NM
    NAMES arm-none-eabi-nm
    HINTS ${hints_paths})

find_program(ARM_LD_TOOL
    NAMES arm-none-eabi-ld
    HINTS ${hints_paths})

find_program(ARM_APP_SIZE_TOOL
    NAMES arm-none-eabi-size
    HINTS ${hints_paths})

find_program(ARM_OBJ_COPY_TOOL
    NAMES arm-none-eabi-objcopy
    HINTS ${hints_paths})

find_program(ARM_OBJ_DUMP_TOOL
    NAMES arm-none-eabi-objdump
    HINTS ${hints_paths})

find_program(ARM_DEBUG_TOOL
    NAMES arm-none-eabi-gdb
    HINTS ${hints_paths})