//
// Created by huan.yang on 2024-05-11.
//

#pragma once

#include <map>
#include <vector>
#include <atomic>

#include "disk/disk_manager.h"
#include "common/macro.h"
#include "common/type.h"
#include "lru_replace.h"

namespace GBSecond {

    /**
     * 缓存池
     * @author huan.yang
     */
    class BufferPoolManager {
    public:
        explicit BufferPoolManager(DiskManager *diskManager,size_t pageSize) : diskManager_(diskManager) {
            pageSize_ = pageSize;
            for (size_t index = 0; index < pageSize; index++) {
                free_frames_.push_back(index);
            }
            pages_ = new Page[pageSize];
        }
        BufferPoolManager(const BufferPoolManager &bufferPoolManager) = delete;
        BufferPoolManager& operator=(const BufferPoolManager &bufferPoolManager) = delete;

        ~BufferPoolManager() {
            delete [] pages_;
            delete diskManager_;
        }

        /**
         * 创建一个Page
         * @return
         */
        auto NewPage() -> Page*;

        /**
         * 删除一个Page
         * @param pageId pageId
         * @return result
         */
        auto Remove(page_id_t pageId) -> bool;

        /**
         * 获取一个Page
         * @param pageId pageId
         * @return Page
         */
        auto FetchPage(page_id_t pageId) -> Page*;

        /**
         * 解除固定的Page
         * @param pageId PageId
         * @return result
         */
        auto UnPin(page_id_t pageId) -> bool;

        /**
         * 获取下一个PageId
         * @return PageId
         */
        auto GetNextPageId() -> page_id_t {
            return nextPageId_.fetch_add(1);
        }

    private:
        DiskManager *diskManager_;

        Page *pages_;

        __attribute_maybe_unused__ size_t pageSize_;

        std::map<page_id_t,frame_id_t> page_table_;

        std::vector<frame_id_t> free_frames_;

        std::atomic<page_id_t> nextPageId_{0};

        std::mutex latch_;

        LruReplace lruReplace;

        std::vector<page_id_t> pin_pages_;

    };

}