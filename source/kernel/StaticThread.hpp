#ifndef KERNEL_STATICTHREAD_HPP
#define KERNEL_STATICTHREAD_HPP

#include "infra/util/Function.hpp"
#include "kernel/Stack.hpp"
#include "kernel/ThreadBase.hpp"
#include <array>
#include <memory>

template <typename T>
struct StackDeleter
{
    constexpr StackDeleter() = default;

    void operator()(T*) const
    {}
};

namespace kernel
{
    template <std::size_t StackSize>
    struct StaticThread: ThreadBase
    {
        explicit StaticThread(std::uint8_t priority, infra::Function<void()> entry);

    protected:
        void Run() override;

    private:
        std::aligned_storage_t<StackSize> stackStorage;
        infra::Function<void()> entry;
    };

    template <std::size_t StackSize>
    StaticThread<StackSize>::StaticThread(std::uint8_t priority, infra::Function<void()> entry)
        : ThreadBase{priority, Stack(StackUniquePtr(&stackStorage, [](void*) {}), StackSize)}
        , entry{entry}
    {
        ThreadBase::Start();
    }

    template <std::size_t StackSize>
    void StaticThread<StackSize>::Run()
    {
        entry();
    }
}

#endif
