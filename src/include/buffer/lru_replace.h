//
// Created by huan.yang on 2024-05-14.
//

#pragma once

#include <list>
#include <vector>
#include <mutex>

#include "common/type.h"

namespace GBSecond {

    /**
     * 过期替换策略
     * @author huan.yang
     * 读取文件是逐个读取，因此不需要考虑循环读取的问题
     */
    class LruReplace {

    public:
        explicit LruReplace(){}
        ~LruReplace() = default;

        /**
         * 设置是否固定
         * @param frameId frameId
         * @param isPin 是否固定
         */
        auto SetPin(frame_id_t frameId,bool isPin) -> void;

        /**
         * 获取一个可用的/可失效的frameId
         * @return frameId
         */
        auto Evict() -> frame_id_t;

        /**
         * 删除
         * @param frameId frameId
         */
        auto Remove(frame_id_t frameId) -> void;

        /**
         * 访问一个Frame
         * @frame_id_t frameId
         */
        auto Fetch(frame_id_t frameId) -> void;


    private:

        std::list<frame_id_t> frames_;

        std::vector<frame_id_t> pins_;

        std::size_t pin_count_{};

        std::size_t frame_size_{};
    };

}

