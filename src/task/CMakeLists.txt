add_library(gbSecond_task OBJECT mutex_queue.cpp thread_pool_manager.cpp)

SET(10G_lib ${10G_lib} $<TARGET_OBJECTS:gbSecond_task> PARENT_SCOPE)