//
// Created by huan.yang on 2024-05-21.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "common/type.h"
#include "disk/disk_manager.h"


namespace GBSecond {

    /**
     * 任务类型
     */
    enum class TaskType {
        TASK,
        STOP
    };

    class Task{
    public:
        explicit Task(page_id_t pageId,std::vector<Task> *residueCache,DiskManager *diskManager,TaskType taskType,size_t readSize = PAGE_SIZE) noexcept :
        pageId_(pageId),residue_cache_(residueCache),diskManager_(diskManager),taskType_(taskType),read_size_(readSize) {}
        ~Task() = default;
//        Task(const Task &task) = delete;
//        auto operator=(const Task &task) -> Task& = delete;
//        Task(Task &&task) = delete;
//        auto operator=(Task &&task) -> Task& = delete;

        inline auto GetPageId() -> page_id_t { return pageId_;}
        inline auto SetPageId(page_id_t pageId) -> void { pageId_ = pageId;}
        inline auto GetResidue() -> std::string { return residue_;}
        inline auto SetResidue(const std::string &residue) -> void { residue_ = residue;}
        inline auto GetTaskType() -> TaskType { return taskType_;}
        inline auto SetTaskType(TaskType taskType) -> void { taskType_ = taskType;}
        inline auto GetReadSize() -> size_t { return read_size_;}
        auto ReadData(size_t readSize) -> std::stringstream;

    private:
        page_id_t pageId_;
        std::string residue_;
        __attribute_maybe_unused__ std::vector<Task> *residue_cache_{nullptr};
        DiskManager *diskManager_;
        TaskType taskType_;
        size_t read_size_{0};
    } ;

}
