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

        /**
         * 通过Boyer-Moore算法进行汇总
         * @return count
         */
        static auto BMCount(char *data, size_t dataSize,std::string &pat) noexcept -> long long;
    private:

        static auto badCharHeuristic(std::string &pat,size_t m,int badChar[]) -> void;

    };
}