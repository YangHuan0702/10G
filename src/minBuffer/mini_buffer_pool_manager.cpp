//
// Created by huan.yang on 2024-05-28.
//

#include "minBuf/mini_buffer_pool_manager.h"

namespace GBSecond {


    auto MiniBufferPoolManager::GetNextPage() -> Page * {

        page_id_t currentPage = next_page_id_.fetch_add(1);

        if (currentPage >= static_cast<page_id_t>(page_sum_) ) {
            return nullptr;
        }

        size_t readSize = static_cast<size_t>(currentPage) == page_sum_ - 1 ? overflow_size_ : PAGE_SIZE;
        size_t frameId = currentPage % page_pool_size_;

        Page *page = &pages_[frameId];
        if (currentPage >= static_cast<page_id_t> (page_pool_size_)) {
            page->WLock();
            page->SetPageSize(readSize);
            disk->Read(page);
            page->WUnLock();
        }
        return page;
    }
}
