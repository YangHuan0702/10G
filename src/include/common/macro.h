//
// Created by huan.yang on 2024-04-29.
//

#pragma once
#include <string>

namespace GBSecond {

//#define PAGE_SIZE 4096 17s
//#define PAGE_SIZE 16384 7s
#define PAGE_SIZE 16384
//#define PAGE_SIZE 32768 11s
//#define PAGE_SIZE 24576 10s
//#define PAGE_SIZE 24576 10s

#define SEEKG_POS(pageId) (PAGE_SIZE * pageId)

#define BUF_PAGE_SIZE 10

    static const std::string JSON_FILE_PATH = "/home/py/feedback_data.txt";

    static const std::string GB_1_FILE = "/home/py/1G.txt";
}
