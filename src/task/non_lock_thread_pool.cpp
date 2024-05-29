//
// Created by huan.yang on 2024-05-24.
//

#include "task/non_lock_thread_pool.h"
#include "util/string_util.h"
#include <string>

namespace GBSecond {


    auto NonLockThread::Run() -> void {
        static std::string targetKey = "concern";
        t_ = std::thread([this]() {

            Page *page = buffer_->GetNextPage();
            while (page != nullptr) {
                auto count = StringUtil::BMCount(page->GetData(),page->GetPageSize(),targetKey);


//                std::string row{page->GetData(), page->GetPageSize()};
//                size_t pos = 0;
//                long long count = 0;
//                while ((pos = row.find(targetKey, pos)) != std::string::npos) {
//                    pos += targetKey.length();
//                    count++;
//                }

                this->count_->fetch_add(count);
                page = buffer_->GetNextPage();
            }
//            page_id_t processToPage = this->page_->fetch_add(1);

//            while (processToPage < this->max_page_) {
//                auto readSize = processToPage == this->max_page_ - 1 ? this->overflow_ : PAGE_SIZE;
//                auto ss = disk_->ReadChar(processToPage, readSize);
//
//                std::string row{ss.get(), readSize};
//                long long count{0};
//                size_t pos = 0;
//                while ((pos = row.find(targetKey, pos)) != std::string::npos) {
//                    pos += targetKey.length();
//                    count++;
//                }
////                std::cout << "Process Page : " << processToPage << std::endl;
//                this->count_->fetch_add(count);
//                processToPage = this->page_->fetch_add(1);
//            }
        });
    }


    auto NonLockThreadPoolManager::Start() -> void {
        std::for_each(threads_.begin(), threads_.end(), [&](NonLockThread &thread) {
            thread.Run();
        });
    }

    auto NonLockThreadPoolManager::Wait() -> void {
        std::for_each(threads_.begin(), threads_.end(), [&](NonLockThread &thread) {
            thread.Join();
        });
    }

}
