//
// Created by huan.yang on 2024-05-21.
//

#include <gtest/gtest.h>
#include <memory>
#include "task/mutex_queue.h"
#include "task/thread_pool_managerl.h"
#include "disk/disk_page_manager.h"
#include "common/macro.h"

namespace GBSecond{
    TEST(Task, ThreadPoolTest) {
        size_t core = 5;
        size_t max = 10;
        size_t seconds = 3;

        auto capacity = std::make_shared<SynchronizedQueue<Task>>();
        std::function<bool (Task&&)> function;

        ThreadPoolManager<Task> threadPoolManager(core,max,capacity,seconds, function);

        std::vector<Task> residueCache;

        DiskPageManager diskPageManager(GB_1_FILE);

        threadPoolManager.Stop();

        Task task{0,&residueCache,&diskPageManager,TaskType::TASK};

        threadPoolManager.Execute(task);

        threadPoolManager.Stop();
        threadPoolManager.Wait();
    }
}