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
        virtual ~DiskManager() {};


        /**
         * 读取Page，offset为Page的id
         * @param page
         * @return
         */
        virtual auto Read(Page *page) -> bool = 0;

        /**
         * 根据PageId读取数据
         * @param pageId pageid
         * @return datas
         */
        virtual auto Read(page_id_t pageId) -> std::string = 0;

        /**
         * 根据PageId读取数据
         * @param pageId pageId
         * @param readSize readSize
         * @return
         */
        virtual auto Read(page_id_t pageId,size_t readSize) -> std::string = 0;

    };


}