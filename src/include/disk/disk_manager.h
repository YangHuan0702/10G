//
// Created by huan.yang on 2024-05-14.
//

#pragma once
#include <string>
#include <fstream>
#include "page/page.h"

namespace GBSecond{


    /**
     * 磁盘管理器
     * @author huan.yang
     */
    class DiskManager {
    public:
        explicit DiskManager() = default;
        virtual ~DiskManager() = 0;


        /**
         * 读取Page，offset为Page的id
         * @param page
         * @return
         */
        virtual auto Read(Page *page) -> bool = 0;
    };


}