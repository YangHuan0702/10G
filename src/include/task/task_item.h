//
// Created by huan.yang on 2024-05-21.
//

#pragma once

#include <string>
#include <vector>

#include "common/type.h"


namespace GBSecond {

    class Task{
    public:
        explicit Task(page_id_t pageId,std::vector<Task> *residueCache) noexcept : pageId_(pageId),residue_cache_(residueCache){}
        ~Task() = default;
        Task(const Task &task) = delete;
        auto operator=(const Task &task) -> Task& = delete;
        Task(Task &&task) = delete;
        auto operator=(Task &&task) -> Task& = delete;

    private:
        page_id_t pageId_;
        std::string residue_;
        std::vector<Task> *residue_cache_{nullptr};
    } ;

}
