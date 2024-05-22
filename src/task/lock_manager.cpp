//
// Created by huan.yang on 2024-05-21.
//


#include "task/lock_manager.h"

namespace GBSecond{


    auto LockManager::Wait() -> void {
        std::unique_lock<std::mutex> ul(mutex_);
        cv_.wait(ul);
    }

    auto LockManager::Notify() -> void {
        cv_.notify_one();
    }

    auto LockManager::NotifyAll() -> void {
        cv_.notify_all();
    }

}
