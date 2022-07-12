add_library(hal.cortex.kernel OBJECT)

target_link_libraries(hal.cortex.kernel PUBLIC
    hal.cortex
    kernel
)

target_sources(hal.cortex.kernel PRIVATE
    PendSV_Handler.cpp
    RequestContextSwitch.cpp
    StackAlignment.cpp
    StackFrame.cpp
    StackFrame.hpp
)

target_compile_features(hal.cortex.kernel PUBLIC cxx_std_17)