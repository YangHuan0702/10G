//
// Created by huan.yang on 2024-05-16.
//

#pragma once

#include <string>
#include <list>
#include <shared_mutex>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <thread>
#include <functional>
#include <chrono>
#include <algorithm>


#include "common/type.h"
#include "mutex_queue.h"
#include "task_item.h"
#include "lock_manager.h"

namespace GBSecond {

    enum class ThreadStatus {
        CREATE,
        READY,
        RUNNING,
    };



    /**
     * 线程类
     */

    class TaskHandlerThread {
    public:
        explicit TaskHandlerThread(bool isCore,std::shared_ptr<CapacityManager<Task>> queue,size_t seconds,
                                   std::shared_ptr<LockManager> lockManager)  noexcept {
            // Reference to non-static member function must be called; did you mean to call it with no arguments?
            isCore_ = isCore;
            free_times_ = std::chrono::system_clock::now();
            queue_ = std::move(queue);
            free_seconds_ = seconds;
            lock_ = lockManager;
            threadStatus_ = ThreadStatus::CREATE;
        };
        ~TaskHandlerThread() noexcept {
            if (thread_.joinable()) {
                thread_.join();
            }
        }

        TaskHandlerThread(const TaskHandlerThread &t) = delete;
        auto operator=(const TaskHandlerThread &t) -> TaskHandlerThread& = delete;
        TaskHandlerThread(TaskHandlerThread &&t) {
            queue_ = t.queue_;
            isCore_ = t.isCore_;
            free_times_ = std::chrono::system_clock::now();
            free_seconds_ = t.free_seconds_;
            lock_ = t.lock_;
            std::cout << "Move desr" << std::endl;
        };
        auto operator=(TaskHandlerThread &&t) -> TaskHandlerThread& {
            queue_ = t.queue_;
            isCore_ = t.isCore_;
            free_times_ = std::chrono::system_clock::now();
            free_seconds_ = t.free_seconds_;
            lock_ = t.lock_;
            return *this;
        };


        /**
         * 启动线程
         */
        auto Start() -> void {
            threadStatus_ = ThreadStatus::READY;
            thread_ = std::thread([this] {
                if (this->lock_.get() == nullptr) {
                    throw std::runtime_error("LockManager is nullptr.");
                }
                this->Run();
            });
        }

        /**
         * 线程运行
         */
        auto Run() -> void;

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

        inline auto GetStatus() -> ThreadStatus { return threadStatus_;}


    private:
        __attribute_maybe_unused__ bool isCore_{false};

        std::thread thread_;

        ThreadStatus threadStatus_{ThreadStatus::READY};

        std::chrono::system_clock::time_point free_times_;

        std::shared_ptr<CapacityManager<Task>> queue_;

        __attribute_maybe_unused__ size_t free_seconds_{};

        std::shared_ptr<LockManager> lock_;
    };


    TASK_MACRO
    class ThreadPoolManager {

    public:
        explicit ThreadPoolManager(size_t core,size_t max,std::unique_ptr<SynchronizedQueue<T>> &queue,
                                   size_t activeTime,std::function<bool (T&&)> refusalPolicy)
                                   : core_(core),max_(max),active_times_(activeTime),refusal_policy_(refusalPolicy){
            queue_ = std::move(queue);
            lockManager_ = std::make_shared<LockManager>();
            cores_.reserve(core);
            for (size_t i = 0; i < core; ++i){
                cores_.emplace_back(true,queue_,activeTime,lockManager_);
                // 启动核心线程
            }
            std::for_each(cores_.begin(),cores_.end(),[&](TaskHandlerThread &taskHandler) {
                taskHandler.Start();
            });
            current_size_ = core;
        }
        ~ThreadPoolManager() = default;
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

        /**
         * 停止线程
         */
        auto Stop() noexcept -> void;


        auto Wait() noexcept -> void;

    private:

        /**
         * 是否所有的核心线程都处于工作状态
         * @return bool
         */
        auto BusyForAllCores() -> bool;

        std::mutex latch_;
        std::condition_variable cv_;

        std::shared_ptr<LockManager> lockManager_;

        // 任务的缓冲队列
        std::shared_ptr<CapacityManager<T>> queue_;

        // 需要合并的任务操作
        std::vector<T> need_merge_task_;

        // 核心线程数
        __attribute_maybe_unused__ size_t core_;

        // 最大线程数
        size_t max_;

        // 当前线程数
        std::atomic<size_t> current_size_{0};

        std::vector<size_t> free_core_threads_;

        // 空闲存活时间
        size_t active_times_;

        // 拒绝策略
        std::function<bool (T&&)> refusal_policy_{nullptr};

        // 线程
        std::vector<TaskHandlerThread> cores_;
        std::vector<TaskHandlerThread> works_;
    };

}
