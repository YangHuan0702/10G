//
// Created by huan.yang on 2024-05-24.
//

#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <functional>

#include "common/type.h"
#include "disk/disk_page_manager.h"
#include "minBuf/mini_buffer_pool_manager.h"

#include "task_item.h"

namespace GBSecond {

    class NonLockThread {
    public:
        explicit NonLockThread(std::atomic<page_id_t> *page,std::atomic_int64_t *count,int maxPage,
                               DiskPageManager *disk_,size_t lastPageSize,MiniBufferPoolManager *buffer)
                               : page_(page),count_(count),max_page_(maxPage),disk_(disk_),overflow_(lastPageSize),buffer_(buffer) {
        }
        ~NonLockThread() {
            if (t_.joinable()) {
                t_.join();
            }
        };
        NonLockThread(const NonLockThread &t) {
            page_ = t.page_;
            count_ = t.count_;
            max_page_ = t.max_page_;
            disk_ = t.disk_;
            overflow_ = t.overflow_;
        };
        auto operator=(const NonLockThread &t) -> NonLockThread& = delete;
        NonLockThread(NonLockThread &&t) = delete;
        auto operator=(NonLockThread &&t) -> NonLockThread& = delete;


        auto Join() -> void {
            if (t_.joinable()) {
                t_.join();
            }
        }

        /**
         * 运行线程
         */
        auto Run() -> void ;

    private:
        std::thread t_;

        std::atomic<page_id_t> *page_;

        std::atomic_int64_t *count_;

        int max_page_;

        DiskPageManager *disk_;

        size_t overflow_;

        MiniBufferPoolManager *buffer_;


    };


    class NonLockThreadPoolManager {

    public:
        explicit NonLockThreadPoolManager(int cores,int maxPage,DiskPageManager *disk,size_t lastPageSize,MiniBufferPoolManager *bufferPoolManager) : cores_(cores),max_page_(maxPage){
            threads_.reserve(cores_);
            for (int i = 0; i < cores_; ++i) {
                threads_.emplace_back(&page,&count_,max_page_,disk,lastPageSize,bufferPoolManager);
            }
        }

        /**
         * 启动线程
         */
        auto Start() -> void;

        /**
         * 等待线程结束
         */
        auto Wait() -> void;


        auto GetCount() -> std::atomic_int64_t {
            return count_.load();
        }


    private:

        // 线程数
        int cores_{0};

        int max_page_{0};

        std::atomic_int64_t count_{0};

        std::atomic<page_id_t> page{0};

        std::vector<NonLockThread> threads_;

    };

}
