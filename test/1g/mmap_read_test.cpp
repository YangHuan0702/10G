//
// Created by huan.yang on 2024-05-13.
//

#include <gtest/gtest.h>
#include <sys/mman.h>
#include "common/macro.h"
#include <chrono>
#include <filesystem>
#include <sstream>
#include <fstream>

TEST(MMapTest,BasicRead) {
    std::string targetKey = "concern";
    // 45848
    std::ifstream is(GBSecond::JSON_FILE_PATH, std::ios::in);
    if (!is.is_open()) {
        std::cout << "File Open fail." << std::endl;
        return;
    }
    size_t fileSize = std::filesystem::file_size(GBSecond::JSON_FILE_PATH);

    auto getFd = [](std::filebuf &fb) -> int {
    class FileFd : public std::filebuf {
    public:
        int handler() { return _M_file.fd();}
    };
    return static_cast<FileFd&>(fb).handler();
    };

    int fd = getFd(*is.rdbuf());

    char *addr = static_cast<char*>(mmap(nullptr,fileSize,PROT_READ,MAP_PRIVATE,fd,0));
//    std::stringstream ss(std::string(addr,fileSize));

    auto startTime = std::chrono::system_clock::now();
    char *start = addr;
    char *end = addr + fileSize;
    size_t count = 0;
    while (start < end) {
        char *rowData = static_cast<char*>(memchr(start,'\n',end - start));
        if (rowData == nullptr) {
            break;
        }
        size_t rowLen = rowData - start;
        std::string strRow(start,rowLen);
        size_t pos = 0;
        while ((pos = strRow.find(targetKey,pos)) != std::string::npos) {
            count++;
            pos += targetKey.length();
        }
        start = rowData +1;
    }
    auto endTime = std::chrono::system_clock::now();

    auto mill = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    munmap(addr,fileSize);
    is.close();
    std::cout << GBSecond::JSON_FILE_PATH << " in the " <<  targetKey << " nums :" << count << " times : " << mill.count() <<  std::endl;
}


TEST(MMapTest, GetFileNameTest) {
    std::string path = "/usr/bin/nginx";
    size_t nameBegin ;
    if ((nameBegin = path.find_last_of('/')) != std::string::npos) {
        std::cout << "======= file Name : " << path.substr(nameBegin + 1,path.size() - 1) << std::endl;
    }
}