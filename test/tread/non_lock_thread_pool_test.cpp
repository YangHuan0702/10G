//
// Created by huan.yang on 2024-05-24.
//
#include <filesystem>
#include <gtest/gtest.h>
#include <chrono>

#include "common/macro.h"
#include "task/non_lock_thread_pool.h"

using namespace GBSecond;


TEST(NonLockThreadTest,UnitTest) {

    auto fileSize = std::filesystem::file_size(GB_1_FILE);

    auto *diskPageManager = new DiskPageManager(GB_1_FILE);

    auto nums = fileSize % PAGE_SIZE == 0 ? fileSize / PAGE_SIZE : fileSize / PAGE_SIZE + 1;

    auto overflowNums = fileSize % PAGE_SIZE;

    int cores = 10;

    auto threadPool = NonLockThreadPoolManager(cores,nums,diskPageManager,overflowNums,nullptr);

    auto start = std::chrono::system_clock::now();
    threadPool.Start();
    threadPool.Wait();
    auto end = std::chrono::system_clock::now();

    auto latch = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Count : " << threadPool.GetCount() << " times: " << latch.count() << std::endl;
}


