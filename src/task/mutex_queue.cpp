//
// Created by huan.yang on 2024-05-20.
//
#include <iostream>

#include "task/mutex_queue.h"
#include "task/task_item.h"

namespace GBSecond {

    TASK_MACRO
    auto SynchronizedQueue<T>::Push(const T &t) noexcept -> bool {
        std::lock_guard<std::mutex> guard(lock_);
        task_.push(t);
        queue_size_++;
        return true;
    }


    TASK_MACRO
    auto SynchronizedQueue<T>::Pop() noexcept -> T {
        std::lock_guard<std::mutex> guard(lock_);
        auto r = task_.front();
        task_.pop();
        queue_size_--;
        return r;
    }

    TASK_MACRO
    auto SynchronizedQueue<T>::GetSize() noexcept -> size_t {
        std::lock_guard<std::mutex> guard(lock_);
        return queue_size_;
    }


    template class SynchronizedQueue<Task>;
}