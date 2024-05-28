//
// Created by huan.yang on 2024-05-28.
//

#include "util/string_util.h"

#include <iostream>

namespace GBSecond {

    auto StringUtil::count(std::string_view &ss) noexcept -> long long {
        std::string targetKey = "concern";

        auto size = ss.size();
        long long r = 0;
        size_t index = 0;
        size_t j = index + targetKey.size() - 1;
        for (; j < size; index++, j++) {
            std::string_view subStr = ss.substr(index, targetKey.size());
            if (subStr == targetKey) {
                r++;
            }
        }
        return r;
    }

}