//
// Created by huan.yang on 2024-05-16.
//

#pragma once

#include <string>
#include <list>
#include <shared_mutex>
#include <memory>
#include <thread>
#include <functional>
#include <chrono>

#include "common/type.h"
#include "capacity_manager.h"

namespace GBSecond {

    /**
     * 线程类
     */
    class TaskHandlerThread {
    public:
        template<typename Callable,typename ... Args>
        explicit TaskHandlerThread(bool isCore,Callable &&callable,Args&&... args)  noexcept : isCore_(isCore) {
            auto boundFunc = std::bind(std::forward<Callable>(callable),std::forward<Args>(args)...);
            thread_ = std::thread([this,boundFunc] {
                do {
                    boundFunc();

                } while (this->isCore_);
            });
        };
        ~TaskHandlerThread() noexcept {
            if (thread_.joinable()) {
                thread_.join();
            }
        }

        TaskHandlerThread(const TaskHandlerThread &t) =delete;
        auto operator=(const TaskHandlerThread &t) = delete;
        TaskHandlerThread(TaskHandlerThread &&t) = delete;
        auto operator=(TaskHandlerThread &&t) = delete;

        auto Join() -> void {
            if (thread_.joinable()) {
                thread_.join();
            }
        }

        auto Detach() -> void {
            if (thread_.joinable()) {
                thread_.detach();
            }
        }

    private:
        bool isCore_{false};

        std::thread thread_;
    };


    TASK_MACRO
    class ThreadPoolManager {

    public:
        explicit ThreadPoolManager(size_t core,size_t max,std::unique_ptr<CapacityManager<T>> queue,
                                   std::chrono::seconds activeTime,std::function<void (T)> refusalPolicy)
                                   : queue_(std::move(queue)),core_(core),max_(max),active_times_(activeTime),refusal_policy_(refusalPolicy){

        }
        ~ThreadPoolManager() {
            if (current_size_ > 0) {
                for (size_t i = 0; i < current_size_; i++) {
                    threads_[i].Detach();
                }

                delete [] threads_;
            }
        }
        ThreadPoolManager(const ThreadPoolManager &threadPoolManager) = delete;
        ThreadPoolManager(ThreadPoolManager &&threadPoolManager) = delete;
        auto operator=(ThreadPoolManager &threadPoolManager) -> ThreadPoolManager& = delete;
        auto operator=(ThreadPoolManager &&threadPoolManager) -> ThreadPoolManager& = delete;

        /**
         * 添加任务
         * @param t 任务
         * @return 是否添加成功
         */
        auto Execute(T &t) noexcept -> bool;


    private:

        std::shared_mutex rw_latch_;

        // 任务的缓冲队列
        std::unique_ptr<CapacityManager<T>> queue_;

        // 需要合并的任务操作
        std::vector<T> need_merge_task_;

        // 核心线程数
        size_t core_;

        // 最大线程数
        size_t max_;

        // 当前线程数
        size_t current_size_;

        // 空闲存活时间
        std::chrono::seconds active_times_;

        // 拒绝策略
        std::function<void (T)> refusal_policy_;

        // 线程
        TaskHandlerThread *threads_;
    };

}
