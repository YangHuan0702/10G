//
// Created by huan.yang on 2024-05-21.
//

#include "task/thread_pool_managerl.h"
#include "task/task_item.h"

namespace GBSecond {

    TASK_MACRO
    auto ThreadPoolManager<T>::Execute(T &t) noexcept -> bool {

        return false;
    }



    template class ThreadPoolManager<Task>;
}