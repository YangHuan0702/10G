//
// Created by huan.yang on 2024-05-20.
//

#include "task/mutex_queue.h"
#include <thread>

namespace GBSecond {

    TASK_MACRO
    auto SynchronizedQueue<T>::Push(const T &t) noexcept -> void {

    }


    TASK_MACRO
    auto SynchronizedQueue<T>::Pop() noexcept -> T & {

    }

    TASK_MACRO
    auto SynchronizedQueue<T>::GetSize() noexcept -> size_t {

        return 0;
    }


}