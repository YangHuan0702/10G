//
// Created by huan.yang on 2024-04-29.
//

#pragma once
#include <string>

namespace GBSecond {

#define PAGE_SIZE 4096

#define SEEKG_POS(pageId) (PAGE_SIZE * pageId)

#define BUF_PAGE_SIZE 10

    static const std::string JSON_FILE_PATH = "/home/py/feedback_data.txt";

    static const std::string GB_1_FILE = "/home/py/1G.txt";
}
