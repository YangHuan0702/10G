//
// Created by huan.yang on 2024-05-11.
//

#pragma once

#include "disk/disk_manager.h"
#include "common/macro.h"


namespace GBSecond {


    class BufferPoolManager {

    private:
        DiskManager *diskManager;

        Page *pages;

    };

}