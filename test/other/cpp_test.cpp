//
// Created by huan.yang on 2024-05-14.
//

#include <gtest/gtest.h>

#include <atomic>
#include "common/type.h"

TEST(CPP,AtomicTest)  {
    std::atomic<GBSecond::page_id_t> nextPageId(0);

    GBSecond::page_id_t pageId1 = nextPageId.fetch_add(1);
    ASSERT_EQ(pageId1,0);

    GBSecond::page_id_t pageId2 = nextPageId.fetch_add(1);
    ASSERT_EQ(pageId2,1);

}