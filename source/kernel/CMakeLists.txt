
add_library(kernel STATIC)

target_include_directories(kernel PUBLIC
    ../
)

target_link_libraries(kernel PUBLIC
    infra.util
)

target_sources(kernel PRIVATE
    arch/RequestContextSwitch.hpp

    Configuration.hpp
    EventDispatcher.cpp
    EventDispatcher.hpp
    IdleThread.cpp
    IdleThread.hpp
    MainThread.cpp
    MainThread.hpp
    Scheduler.cpp
    Scheduler.hpp
    SchedulerInstance.cpp
    SchedulerInstance.hpp
    Stack.cpp
    Stack.hpp
    StaticThread.hpp
    Thread.hpp
    ThreadBase.cpp
    ThreadBase.hpp
    ThreadControlBlock.cpp
    ThreadControlBlock.hpp
    ThreadList.hpp
    ThreadRunner.cpp
    ThreadRunner.hpp
)

target_compile_features(kernel PUBLIC cxx_std_17)