//
// Created by huan.yang on 2024-05-14.
//

#pragma once

#include "disk_manager.h"

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

    private:
        __attribute_maybe_unused__ std::string file_name_;
        __attribute_maybe_unused__ std::string file_path_;
        __attribute_maybe_unused__ size_t file_size_;

        std::fstream *fs_;
    };

}
