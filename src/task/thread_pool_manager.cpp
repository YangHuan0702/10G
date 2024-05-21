//
// Created by huan.yang on 2024-05-21.
//
#include <iostream>

#include "task/thread_pool_managerl.h"
#include "task/task_item.h"
namespace GBSecond {

    auto TaskHandlerThread::Run() -> void {
        std::string targetKey = "concern";
        threadStatus_ = ThreadStatus::RUNNING;

        while (true) {
            cv_.wait(lock_);
            auto task = queue_->Pop();

            auto ss = task.ReadData();

            std::string row;
            long long count {0};
            while (std::getline(ss, row)) {
                size_t pos = 0;
                while ((pos = row.find(targetKey, pos)) != std::string::npos) {
                    pos += targetKey.length();
                    count++;
                }
            }

            std::cout << "count : " << count << std::endl;
        }
    }


    TASK_MACRO
    auto ThreadPoolManager<T>::Execute(T &t) noexcept -> bool {
        std::lock_guard<std::mutex> guard(latch_);
        // 执行拒绝策略
        if (current_size_ >= max_) {
            return refusal_policy_(std::move(t));
        }

        // 是否所有核心线程都处于工作状态，如果是的话，需要新建工作线程来加大处理速度
        if (BusyForAllCores()) {
            auto &ref = works_.emplace_back(false,queue_,active_times_,thread_latch_);
            ref.Run();
        }
        queue_->Push(t);
        return queue_->Push(t);
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


    template
    class ThreadPoolManager<Task>;
}