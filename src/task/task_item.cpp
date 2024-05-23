//
// Created by huan.yang on 2024-05-21.
//

#include "task/task_item.h"

namespace GBSecond {


    auto Task::ReadData(size_t pageSize) -> std::stringstream {
        auto rowInfo = diskManager_->Read(GetPageId(),pageSize);
        std::stringstream ss(rowInfo);
        return ss;
    }

}