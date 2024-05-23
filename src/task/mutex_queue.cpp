//
// Created by huan.yang on 2024-05-20.
//
#include <iostream>

#include "task/mutex_queue.h"
#include "task/task_item.h"

namespace GBSecond {

    TASK_MACRO
    auto SynchronizedQueue<T>::Push(const T &t) noexcept -> bool {
        std::unique_lock<std::mutex> lock(lock_);
        task_.push(t);
        queue_size_++;
        cv_.notify_all();
        return true;
    }


    TASK_MACRO
    auto SynchronizedQueue<T>::Pop() noexcept -> T {
//        for(;queue_size_<=0;) {}
        std::unique_lock<std::mutex> lock(lock_);
        cv_.wait(lock,[this]{ return this->queue_size_ > 0;});
        auto r = task_.front();
        task_.pop();
        queue_size_--;
        std::cout << "process pop : " << this->queue_size_ << std::endl;
        return r;
    }

    TASK_MACRO
    auto SynchronizedQueue<T>::GetSize() noexcept -> size_t {
        return queue_size_;
    }


    template class SynchronizedQueue<Task>;
}