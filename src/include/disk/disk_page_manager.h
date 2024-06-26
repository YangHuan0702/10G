//
// Created by huan.yang on 2024-05-14.
//

#pragma once

#include "disk_manager.h"
#include <memory>

namespace GBSecond {

    class DiskPageManager : public DiskManager {
    public:
        explicit DiskPageManager(const std::string &path);
        ~DiskPageManager() noexcept override;
        DiskPageManager(const DiskPageManager &diskPageManager) = delete;
        DiskPageManager& operator=(const DiskPageManager &diskPageManager) = delete;

        /**
         * 读取Page，offset为Page的id
         * @param page
         * @return
         */
        auto Read(Page *page) -> bool override;

        /**
         * 读取Page
         * @param pageId
         * @return
         */
        auto Read(page_id_t pageId) -> std::string override;

        /**
         * 读取Page
         * @param pageId
         * @param readSize
         * @return
         */
        auto Read(page_id_t pageId, size_t readSize) -> std::string override;

        auto ReadChar(page_id_t pageId, size_t readSize) -> std::shared_ptr<char[]>;


        /**
         * 读取Page
         * @param pageId
         * @param readSize
         * @return
         */
        auto ReadStream(page_id_t pageId,size_t readSize) -> std::stringstream;


    private:
        __attribute_maybe_unused__ std::string file_name_;
        __attribute_maybe_unused__ std::string file_path_;
        __attribute_maybe_unused__ size_t file_size_;

        std::mutex latch_;

        std::fstream *fs_;
    };

}
