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

        /**
         * 读取Page，offset为Page的id
         * @param page
         * @return
         */
        auto Read(Page *page) -> bool override;

    private:
        __attribute_maybe_unused__ std::string file_name_;
        __attribute_maybe_unused__ std::string file_path_;
        __attribute_maybe_unused__ size_t file_size_;

        std::fstream *fs_;
    };

}
