//
// Created by huan.yang on 2024-05-14.
//

#include "buffer/lru_replace.h"
#include <algorithm>

namespace GBSecond{

    auto LruReplace::Remove(GBSecond::frame_id_t frameId) -> void {
        if (std::find(pins_.begin(),pins_.end(),frameId) != pins_.end()) {
            frames_.remove(frameId);
            frame_size_--;
        }
    }

    auto LruReplace::Evict() -> frame_id_t {
        frame_id_t r = -1;
        for (auto item = frames_.rbegin(); item != frames_.rend(); item++) {
            if (std::find(pins_.begin(),pins_.end(),*item) != pins_.end()) {
                frames_.remove(*item);
                frame_size_--;
                r = *item;
                break;
            }
        }
        return r;
    }

    auto LruReplace::Fetch(GBSecond::frame_id_t frameId) -> void {
        if (std::find(frames_.begin(),frames_.end(),frameId) == frames_.end()) {
            frame_size_++;
        }
        frames_.remove(frameId);
        frames_.push_front(frameId);
    }

    auto LruReplace::SetPin(GBSecond::frame_id_t frameId, bool isPin) -> void {
        if (std::find(frames_.begin(),frames_.end(),frameId) == frames_.end()) {
            return;
        }

        auto existPins = std::find(pins_.begin(),pins_.end(),frameId);
        if (existPins == pins_.end() && isPin) {
            pins_.push_back(frameId);
            pin_count_++;
        }
        if (existPins != pins_.end() && !isPin) {
            pins_.erase(std::remove(pins_.begin(),pins_.end(),frameId),pins_.end());
            pin_count_--;
        }
    }

}