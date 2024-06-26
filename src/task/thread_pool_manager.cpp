//
// Created by huan.yang on 2024-05-21.
//
#include <iostream>

#include "task/thread_pool_managerl.h"
#include "task/task_item.h"
namespace GBSecond {

    auto TaskHandlerThread::Run() -> void {
        try {
            std::string targetKey = "concern";
            threadStatus_ = ThreadStatus::RUNNING;

            while (threadStatus_ != ThreadStatus::STOP) {
                if (queue_ == nullptr) {
                    throw std::runtime_error("queue is nullptr.");
                }
                auto task = queue_->Pop();


                if (task.GetTaskType() == TaskType::STOP) {
                    break;
                }
                // Shadow bytes around the buggy address:
                auto ss = task.ReadData(task.GetReadSize());

                std::string row;
                long long count{0};
                while (std::getline(ss, row)) {
                    size_t pos = 0;
                    while ((pos = row.find(targetKey, pos)) != std::string::npos) {
                        pos += targetKey.length();
                        count++;
                    }
                }
                count_->fetch_add(count);
//                count_ += count;
            }
        }catch (std::exception &e) {
            std::cout << "Thread Exec exception ：" << e.what() << std::endl;
        }
        threadStatus_ = ThreadStatus::STOP;
    }


    TASK_MACRO
    auto ThreadPoolManager<T>::Execute(T &t) noexcept -> bool {
        std::lock_guard<std::mutex> guard(latch_);
        // 执行拒绝策略
//        if (current_size_ >= max_) {
//            return refusal_policy_(std::move(t));
//        }

        // 是否所有核心线程都处于工作状态，如果是的话，需要新建工作线程来加大处理速度
//        if (BusyForAllCores()) {
//            auto &ref = works_.emplace_back(false,queue_,active_times_,lockManager_);
//            ref.Run();
//        }
        queue_->Push(t);
        return true;
    }


    TASK_MACRO
    auto ThreadPoolManager<T>::BusyForAllCores() -> bool {
        bool r = true;
        for (auto &t: cores_) {
            if (t.GetStatus() != ThreadStatus::RUNNING) {
                r = false;
                break;
            }
        }
        return r;
    }

    TASK_MACRO
    auto ThreadPoolManager<T>::Stop() noexcept -> void {
        for (size_t index = 0; index < core_; index++) {
            Task task{0,nullptr, nullptr,TaskType::STOP};
            Execute(task);
        }
    }


    TASK_MACRO
    auto ThreadPoolManager<T>::Wait() noexcept -> void {
        try {
            for (auto &item : cores_) {
                item.Join();
            }
        }catch(std::exception &e ){
            std::cout << "Wait throw exception : " << e.what() << std::endl;
        }
    }

    template
    class ThreadPoolManager<Task>;
}