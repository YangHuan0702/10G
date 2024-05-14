//
// Created by huan.yang on 2024-05-14.
//
#pragma once

#include <shared_mutex>
#include <cstring>

#include "common/type.h"
#include "common/macro.h"

namespace GBSecond{

    class Page{
    public:
        explicit Page(page_id_t pageId) : pageId_(pageId){
            memset(data_,0,PAGE_SIZE);
        }
        ~Page() {
            delete [] &data_;
        }
        inline auto SetPageId(page_id_t pageId) -> void { pageId_ = pageId;}
        inline auto GetPageId() -> page_id_t  { return pageId_;}
        inline auto GetData() -> char* { return data_;}
        inline auto SetData(char *data) ->void {
            memcpy(data,data_,PAGE_SIZE);
        }

        inline auto RLock() -> void { rw_latch_.lock_shared();}
        inline auto RUnLock() -> void { rw_latch_.unlock_shared();}
        inline auto WLock() -> void { rw_latch_.lock();}
        inline auto WUnLock() -> void { rw_latch_.unlock();}

    private:

        page_id_t pageId_;

        char data_[PAGE_SIZE];

        std::shared_mutex rw_latch_;
    };

}
