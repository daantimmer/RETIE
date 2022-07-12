#ifndef KERNEL_THREADLIST_HPP
#define KERNEL_THREADLIST_HPP

#include "infra/util/IntrusiveSet.hpp"

namespace kernel
{

    struct ThreadControlBlockItem;

    using ThreadList = infra::IntrusiveSet<ThreadControlBlockItem, std::greater<ThreadControlBlockItem>>;
    using ThreadListNode = ThreadList::NodeType;
}

#endif
