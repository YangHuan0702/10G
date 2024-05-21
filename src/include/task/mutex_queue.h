//
// Created by huan.yang on 2024-05-16.
//

#pragma once


#include "capacity_manager.h"

#include <queue>
#include <mutex>


namespace GBSecond {


    /**
     * 同步队列
     * @tparam T 任务类型
     */
    TASK_MACRO
    class SynchronizedQueue : public virtual CapacityManager<T>{

    public:
        explicit SynchronizedQueue() = default;
        ~SynchronizedQueue() = default;
        SynchronizedQueue(const SynchronizedQueue &queue) = default;
        auto operator=(const SynchronizedQueue &queue) -> SynchronizedQueue& = default;
        SynchronizedQueue(SynchronizedQueue&& queue)  noexcept = default;
        auto operator=(SynchronizedQueue &&queue) noexcept -> SynchronizedQueue& = default;

        /**
         * 提交任务
         * @param t 任务
         * @return 是否添加成功
         */
        auto Push(const T &t) noexcept -> void override;

        /**
         * 弹出一个任务
         * @return 任务
         */
        auto Pop() noexcept -> T& override;

        /**
         * 获取队列当前大小
         * @return
         */
        auto GetSize() noexcept -> size_t;


    private:
        std::queue<T> task_;
        std::mutex lock_;

        size_t queue_size_{0};
    };


}
