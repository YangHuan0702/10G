//
// Created by huan.yang on 2024-05-23.
//

#include <gtest/gtest.h>
#include <chrono>
#include <filesystem>
#include <future>
#include <atomic>

#include "task/mutex_queue.h"
#include "task/thread_pool_managerl.h"
#include "disk/disk_page_manager.h"
#include "common/macro.h"

using namespace GBSecond;

/**
 * 多线程ReadTestUnit
 */
TEST(ThreadPool1GTest,MutileThreadRead){

    size_t core = 5;
    size_t max = 10;
    size_t seconds = 3;

    auto capacity = std::make_shared<SynchronizedQueue<Task>>();
    std::function<bool (Task&&)> function;

    ThreadPoolManager<Task> threadPoolManager(core,max,capacity,seconds, function);

    std::vector<Task> residueCache;

    DiskPageManager diskPageManager(GB_1_FILE);

    auto fileSize = std::filesystem::file_size(GB_1_FILE);

    auto nums = fileSize % PAGE_SIZE == 0 ? fileSize / PAGE_SIZE : fileSize / PAGE_SIZE + 1;

    auto overflowNums = fileSize % PAGE_SIZE;

    auto pageNums = static_cast<page_id_t>(nums);

    auto start = std::chrono::system_clock::now();

    for (page_id_t index = 0; index < pageNums; index++) {
        size_t readSize = index == pageNums - 1 ? overflowNums : PAGE_SIZE;
        Task task{index,&residueCache,&diskPageManager,TaskType::TASK,readSize};
        threadPoolManager.Execute(task);
    }
    threadPoolManager.Stop();
    threadPoolManager.Wait();
    auto end = std::chrono::system_clock::now();


    auto latch = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Processor times : " << latch.count() << " Result: " << threadPoolManager.GetCount() << std::endl;
}


