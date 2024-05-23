//
// Created by huan.yang on 2024-05-16.
//

#pragma once


#include "capacity_manager.h"

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace GBSecond {


    /**
     * 同步队列
     * @tparam T 任务类型
     */
    TASK_MACRO
    class SynchronizedQueue : public virtual CapacityManager<T>{

    public:
        explicit SynchronizedQueue() = default;
        ~SynchronizedQueue() override = default;
        SynchronizedQueue(const SynchronizedQueue &queue) = delete;
        auto operator=(const SynchronizedQueue &queue) -> SynchronizedQueue& = delete;
        SynchronizedQueue(SynchronizedQueue&& queue)  noexcept = delete;
        auto operator=(SynchronizedQueue &&queue) noexcept -> SynchronizedQueue& = delete;

        /**
         * 提交任务
         * @param t 任务
         * @return 是否添加成功
         */
        auto Push(const T &t) noexcept -> bool override;

        /**
         * 弹出一个任务
         * @return 任务
         */
        auto Pop() noexcept -> T override;

        /**
         * 获取队列当前大小
         * @return
         */
        auto GetSize() noexcept -> size_t;


    private:
        std::queue<T> task_;
        std::mutex lock_;

        std::condition_variable cv_;

        std::atomic_int64_t queue_size_{0};
    };


}
