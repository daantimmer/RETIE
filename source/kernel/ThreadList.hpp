#ifndef KERNEL_THREADLIST_HPP
#define KERNEL_THREADLIST_HPP

#include "assert.h"
//
#include "infra/util/IntrusivePriorityQueue.hpp"

namespace kernel
{

    struct ThreadControlBlockItem;

    using ThreadList = infra::IntrusivePriorityQueue<ThreadControlBlockItem>;
    // using ThreadList = infra::IntrusiveSet<ThreadControlBlockItem, std::greater<ThreadControlBlockItem>>;
    using ThreadListNode = ThreadList::NodeType;
}

#endif
