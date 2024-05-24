//
// Created by huan.yang on 2024-05-24.
//

#include "task/non_lock_thread_pool.h"
#include <string>

namespace GBSecond {


    auto NonLockThread::Run() -> void {
        static std::string targetKey = "concern";
        t_ = std::thread([this]() {
            page_id_t processToPage = this->page_->fetch_add(1);
            while (processToPage < this->max_page_) {
                auto ss = disk_->ReadStream(processToPage,processToPage == this->max_page_ - 1 ? this->overflow_ : PAGE_SIZE);

                std::string row;
                long long count{0};
                while (std::getline(ss, row)) {
                    size_t pos = 0;
                    while ((pos = row.find(targetKey, pos)) != std::string::npos) {
                        pos += targetKey.length();
                        count++;
                    }
                }
//                std::cout << "Process Page : " << processToPage << std::endl;
                this->count_->fetch_add(count);
                processToPage = this->page_->fetch_add(1);
            }
        });
    }


    auto NonLockThreadPoolManager::Start() -> void {
        std::for_each(threads_.begin(),threads_.end(),[&] (NonLockThread &thread) {
            thread.Run();
        });
    }

    auto NonLockThreadPoolManager::Wait() -> void {
        std::for_each(threads_.begin(),threads_.end(),[&] (NonLockThread &thread) {
            thread.Join();
        });
    }

}
