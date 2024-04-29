//
// Created by huan.yang on 2024-04-29.
//

#include <gtest/gtest.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

#include "common/macro.h"



/**
* 读取JSON信息
*/
TEST(GBSecondJsonTest, ReadJson) {
    std::cout << "Starting Read JSON Test." << std::endl;
    std::ifstream is(GBSecond::JSON_FILE_PATH, std::ios::in);
    if (!is.is_open()) {
        std::cout << "file Open fail." << std::endl;
    } else {
        std::string jsonLine;
        std::getline(is, jsonLine);
        if (jsonLine.empty()) {
            std::cout << "Read empty Line" << std::endl;
        } else {
            std::cout << jsonLine << std::endl;
        }
    }
    is.close();

    std::cout.flush();
}

