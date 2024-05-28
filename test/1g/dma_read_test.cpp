//
// Created by huan.yang on 2024-05-27.
//

#include <gtest/gtest.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include "common/type.h"
#include "common/macro.h"

using namespace GBSecond;

void aligned_alloc_example(char **buffer, size_t size, size_t alignment) {
    // 使用 posix_memalign 分配对齐的内存
    if (posix_memalign((void **) buffer, alignment, size) != 0) {
        std::cerr << "Failed to allocate aligned memory" << std::endl;
        exit(EXIT_FAILURE);
    }
}

TEST(NonLockThreadTest, MutileThreadDIOTest) {

    static std::string targetKey = "concern";

    int fd;
    char *buffer;

// 分配对齐的内存
    aligned_alloc_example(&buffer, PAGE_SIZE, PAGE_SIZE);

    const char *fileName = "/home/py/1G.txt";
// 打开文件
    fd = open(fileName, O_CREAT | O_RDWR | O_DIRECT, 0644);
    if (fd == -1) {
        std::cerr << "Failed to open file" << std::endl;
        free(buffer);
    } else {

        auto fileSize = std::filesystem::file_size(GB_1_FILE);

        auto nums = fileSize % PAGE_SIZE == 0 ? fileSize / PAGE_SIZE : fileSize / PAGE_SIZE + 1;

        auto overflowNums = fileSize % PAGE_SIZE;

        long long all{};

        auto start = std::chrono::system_clock::now();
        for (size_t index = 0; index < nums; index++) {
            auto readSize = index == nums - 1 ? overflowNums : PAGE_SIZE;
            memset(buffer, 0, PAGE_SIZE); // 清空缓冲区
            read(fd, buffer, readSize);

            std::stringstream ss({buffer, readSize});

            std::string row;
            long long count{0};
            while (std::getline(ss, row)) {
                size_t pos = 0;
                while ((pos = row.find(targetKey, pos)) != std::string::npos) {
                    pos += targetKey.length();
                    count++;
                }
            }
//                std::cout << "Process Page : " << processToPage << std::endl;
            all += count;
        }
        auto end = std::chrono::system_clock::now();

        auto times = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "count : " << all << " times : " << times.count() << "\n";
    }

    close(fd);
    free(buffer);
}