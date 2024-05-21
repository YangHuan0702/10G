//
// Created by huan.yang on 2024-05-20.
//

#pragma once

namespace GBSecond {


#define TASK_MACRO template <typename T>

    TASK_MACRO
    class CapacityManager {
    public:
        virtual ~CapacityManager(){};

        /**
         * 提交任务
         * @param t 任务
         * @return 是否添加成功
         */
        virtual auto Push(const T &t) noexcept -> bool = 0;

        /**
         * 弹出一个任务
         * @return 任务
         */
        virtual auto Pop() noexcept -> T = 0;
    };

}