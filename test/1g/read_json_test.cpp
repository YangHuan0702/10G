//
// Created by huan.yang on 2024-04-29.
//

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "common/macro.h"


/**
* 读取JSON信息
*/
TEST(GBSecondJsonTest, ReadLine) {
    // /usr/bin/clang
    std::string targetKey = "concern";
    std::ifstream is(GBSecond::JSON_FILE_PATH, std::ios::in);
    if (!is.is_open()) {
        std::cout << "file Open fail." << std::endl;
        return;
    }
    std::string jsonLine;
    std::getline(is, jsonLine);
    if (jsonLine.empty()) {
        std::cout << "Read empty Line" << std::endl;
    }
    std::transform(jsonLine.begin(),jsonLine.end(),jsonLine.begin(),[](unsigned char c) { return std::tolower(c);});
    std::cout << jsonLine << std::endl;
    std::stringstream ss(jsonLine);

    size_t pos = 0;
    size_t count = 0;
    while ((pos = jsonLine.find(targetKey,pos)) != std::string::npos) {
        count++;
        pos += targetKey.length();
    }
    std::cout <<  targetKey << " Count : " << count << std::endl;
    is.close();
}


/**
 * 读取1G文件
 */
TEST(GBSecondJsonTest,Read1G) {
    std::string targetKey = "concern";
    std::ifstream is(GBSecond::GB_1_FILE, std::ios::in);
    if (!is.is_open()) {
        std::cout << "file Open fail." << std::endl;
        return;
    }
    auto begin = std::chrono::system_clock::now();
    std::string row;
    size_t count = 0;
    while (std::getline(is,row)) {
        size_t pos = 0;
        while ((pos = row.find(targetKey,pos)) != std::string::npos) {
            pos += targetKey.length();
            count++;
        }
    }
    auto end = std::chrono::system_clock::now();

    auto times = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    // 43715
    std::cout << "1G File Count for Key : " << targetKey << " nums : " << count  << " running :" << times.count() << std::endl;
    is.close();
}