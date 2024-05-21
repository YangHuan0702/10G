//
// Created by huan.yang on 2024-05-21.
//

#include "task/task_item.h"

namespace GBSecond {


    auto Task::ReadData() -> std::stringstream {
        std::stringstream ss(diskManager_->Read(GetPageId()));
        return ss;
    }

}