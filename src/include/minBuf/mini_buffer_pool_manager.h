//
// Created by huan.yang on 2024-05-28.
//
#pragma once

#include <mutex>
#include <vector>
#include <atomic>

#include "common/type.h"
#include "common/macro.h"
#include "disk/disk_page_manager.h"
#include "page/page.h"

namespace GBSecond {

    class MiniBufferPoolManager {

    public:
        explicit MiniBufferPoolManager(DiskPageManager *diskPageManager,size_t pagePoolSize,size_t pageSum,size_t overflowSize):
        disk(diskPageManager),overflow_size_(overflowSize),page_sum_(pageSum),page_pool_size_(pagePoolSize) {
            pages_ = new Page[pagePoolSize];
            for (size_t i = 0; i < pagePoolSize; ++i) {
                Page *page = &pages_[i];
                page->Init();
                page->SetPageId(i);
                page->SetPageSize(PAGE_SIZE);
                diskPageManager->Read(page);
            }
//            next_page_id_ = static_cast<page_id_t>(pagePoolSize);
        }
        ~MiniBufferPoolManager () {
            delete [] pages_;
//            delete disk;
        }
        MiniBufferPoolManager(const MiniBufferPoolManager &) = delete;
        auto operator=(const MiniBufferPoolManager &) -> MiniBufferPoolManager& = delete;
        MiniBufferPoolManager(MiniBufferPoolManager &&) = delete;
        auto operator=(const MiniBufferPoolManager &&) -> MiniBufferPoolManager & = delete;


        /**
         * 获取下一个Page
         * @return
         */
        auto GetNextPage() -> Page*;


    private:

        DiskPageManager *disk;

        __attribute_maybe_unused__ size_t overflow_size_{};

        __attribute_maybe_unused__ size_t page_sum_{};

        __attribute_maybe_unused__ size_t page_pool_size_;

        Page *pages_;

        __attribute_maybe_unused__ std::atomic<page_id_t> next_page_id_{0};

        std::vector<page_id_t> page_pool_{0};
    };

}
