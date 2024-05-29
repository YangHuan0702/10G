//
// Created by huan.yang on 2024-05-28.
//

#include "util/string_util.h"

#include <iostream>

#define NO_OF_CHARS 256

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

    inline int max(int a, int b) {
        return a > b ? a : b;
    }

    auto StringUtil::BMCount(char *data, size_t dataSize,std::string &pat) noexcept -> long long {
        int m = pat.size();
        int n = dataSize;

        int badChar[NO_OF_CHARS];

        badCharHeuristic(pat,m,badChar);

        int s = 0;

        long long r = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            // pattern occurs at shift =
            while ( j >= 0 && pat[j] == data[s + j]) {
                j--;
            }

            if (j < 0) {
                r++;
                s += (s + m < n) ? m - badChar[(int)data[s + m]] : 1;
            } else {
                s += max(1,j - badChar[(int )data[s + j]]);
            }
        }
        return r;
    }


    auto StringUtil::badCharHeuristic(std::string &pat, size_t m, int *badChar) -> void {
        size_t i;

        for (i = 0; i < NO_OF_CHARS ; i++) {
            badChar[i] = -1;
        }

        for (i = 0; i < m; i++) {
            badChar[(int)pat[i]] = i;
        }
    }

}