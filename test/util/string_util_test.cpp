//
// Created by huan.yang on 2024-05-29.
//
#include <gtest/gtest.h>

#include "util/string_util.h"

using namespace GBSecond;

TEST(StringUtilTest,BMCountTest) {
    std::string txt = "abcdAbcabcd";
    std::string pat = "abcd";

    std::cout << "Count : " << StringUtil::BMCount(txt.data(),txt.size(),pat);
}