//
// Created by huan.yang on 2024-05-28.
//
#pragma once
#include <sstream>

namespace GBSecond {


    class StringUtil {
    public:

        /**
         * 统计
         * @param ss
         * @return count
         */
        static auto count(std::string_view &ss) noexcept -> long long;
    };
}