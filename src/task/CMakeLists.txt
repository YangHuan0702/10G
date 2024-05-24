add_library(gbSecond_task OBJECT mutex_queue.cpp thread_pool_manager.cpp task_item.cpp lock_manager.cpp non_lock_thread_pool.cpp)

SET(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:gbSecond_task> PARENT_SCOPE)