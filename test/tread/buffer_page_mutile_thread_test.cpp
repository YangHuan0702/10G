//
// Created by huan.yang on 2024-05-28.
//

#include <gtest/gtest.h>
#include <filesystem>

#include "task/non_lock_thread_pool.h"
#include "minBuf/mini_buffer_pool_manager.h"

namespace GBSecond{


    TEST(BufferRead1GTest,UnitTest) {
        auto fileSize = std::filesystem::file_size(GB_1_FILE);

        auto *diskPageManager = new DiskPageManager(GB_1_FILE);


        auto nums = fileSize % PAGE_SIZE == 0 ? fileSize / PAGE_SIZE : fileSize / PAGE_SIZE + 1;

        auto overflowNums = fileSize % PAGE_SIZE;

        int cores = 20;

        auto *buffer = new MiniBufferPoolManager(diskPageManager,10000,nums,overflowNums);

        auto threadPool = NonLockThreadPoolManager(cores,nums,diskPageManager,overflowNums,buffer);

        auto start = std::chrono::system_clock::now();
        threadPool.Start();
        threadPool.Wait();
        auto end = std::chrono::system_clock::now();

        auto latch = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        // 45828
        std::cout << "Count : " << threadPool.GetCount() << " times: " << latch.count() << std::endl;
        delete diskPageManager;
        delete buffer;
    }

}