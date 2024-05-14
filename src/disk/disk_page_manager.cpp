//
// Created by huan.yang on 2024-05-14.
//
#include "disk/disk_page_manager.h"
#include "common/macro.h"
#include <filesystem>

namespace GBSecond {

    DiskPageManager::DiskPageManager(const std::string &path) {
        fs_ = new std::fstream(path,std::ios::in);
        if (!fs_->is_open()) {
            throw std::runtime_error(path + " open fail~");
        }
        file_size_ = std::filesystem::file_size(path);
        if (file_size_ == 0) {
            throw std::runtime_error(path + " is empty file~");
        }
//        size_t nameBegin;
//        if ((nameBegin = path.find_last_of('/')) != std::string::npos) {
//            file_path_ = path;
//            file_name_ = path.substr(nameBegin + 1,path.size() - 1);
//        }
    }

    DiskPageManager::~DiskPageManager() noexcept {
        fs_->close();
        delete fs_;
    }

    auto DiskPageManager::Read(GBSecond::Page *page) -> bool {
        fs_->seekg(SEEKG_POS(page->GetPageId()));
        fs_->read(page->GetData(),PAGE_SIZE);
        return true;
    }

}