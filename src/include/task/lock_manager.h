//
// Created by huan.yang on 2024-05-21.
//

#pragma once

#include <mutex>
#include <condition_variable>

#include "capacity_manager.h"
#include "task_item.h"

namespace GBSecond{

    class LockManager {

    public:
        // 默认构造函数和析构函数
        LockManager() = default;
        ~LockManager() = default;

        // 禁用复制操作
        LockManager(const LockManager&) = delete;
        LockManager& operator=(const LockManager&) = delete;

        // 禁用移动操作
        LockManager(LockManager&&) = delete;
        LockManager& operator=(LockManager&&) = delete;

        auto Wait() -> void;

        auto Notify() -> void;

        auto NotifyAll() -> void;

    private:
        std::condition_variable cv_;

        std::mutex mutex_;

        std::shared_ptr<SynchronizedQueue<Task>> queue_;
    };

}