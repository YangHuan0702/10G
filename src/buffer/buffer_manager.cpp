//
// Created by huan.yang on 2024-05-11.
//
#include "buffer/buffer_manager.h"
#include <algorithm>

namespace GBSecond {


    auto BufferPoolManager::CreatePage() -> Page * {
        Page *page;
        frame_id_t frameId;
        if (free_frames_.empty()) {
            /**
             * only read, so don`t need check page is dirty and write to disk.
             */
            frameId = lruReplace.Evict();
            if (frameId == -1) {
                throw std::runtime_error("NewPage in the evict frame fail!");
            }
        } else {
            frameId = free_frames_.front();
        }
        page = &pages_[frameId];
        page->SetPageId(GetNextPageId());

        page_table_[frameId] = page->GetPageId();
        free_frames_.erase(std::remove(free_frames_.begin(), free_frames_.end(), frameId), free_frames_.end());
        lruReplace.SetPin(frameId, true);

        page->IncrPin();
        // read row infos for disk.
        diskManager_->Read(page);
        return page;
    }

    auto BufferPoolManager::NewPage() -> Page * {
        std::lock_guard<std::mutex> guard(latch_);
        return CreatePage();
    }


    auto BufferPoolManager::Remove(GBSecond::page_id_t pageId) -> bool {
        std::lock_guard<std::mutex> guard(latch_);

        if (page_table_.find(pageId) != page_table_.end()) {

            Page *page = &pages_[page_table_[pageId]];
            if (page->GetPinCount() > 0) {
                return false;
            }
            free_frames_.push_back(page_table_[pageId]);
            lruReplace.Remove(page_table_[pageId]);
            page_table_.erase(pageId);
        }
        return true;
    }

    auto BufferPoolManager::UnPin(GBSecond::page_id_t pageId) -> bool {
        std::lock_guard<std::mutex> guard(latch_);
        if (page_table_.find(pageId) == page_table_.end()) {
            return false;
        }
        auto *page = &pages_[page_table_[pageId]];
        page->DecrPin();

        if (page->GetPinCount() <= 0) {
            lruReplace.SetPin(page_table_[pageId], false);
        }
        return true;
    }

    auto BufferPoolManager::FetchPage(GBSecond::page_id_t pageId) -> Page * {
        std::lock_guard<std::mutex> guard(latch_);
        Page *page;
        if (page_table_.find(pageId) != page_table_.end()) {
            lruReplace.Fetch(pageId);
            lruReplace.SetPin(page_table_[pageId], true);
            page = &pages_[page_table_[pageId]];
            page->IncrPin();
        } else {
            frame_id_t frameId;
            if (!free_frames_.empty()) {
                frameId = free_frames_.front();
            } else {
                frameId = lruReplace.Evict();
            }
            page = &pages_[frameId];
            page->SetPageId(pageId);
            page->ResetPageData();
            page->SetPinCount(1);
            lruReplace.Fetch(frameId);
            lruReplace.SetPin(frameId, true);
            diskManager_->Read(page);
        }
        return page;
    }

}