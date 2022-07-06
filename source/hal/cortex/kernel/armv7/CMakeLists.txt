add_library(hal.cortex.kernel.armv7 OBJECT)

target_link_libraries(hal.cortex.kernel.armv7 PUBLIC
    hal.cortex.kernel
)

target_sources(hal.cortex.kernel.armv7 PRIVATE
    StackFrame.cpp
    StackFrame.hpp
)

target_compile_features(hal.cortex.kernel.armv7 PUBLIC cxx_std_17)