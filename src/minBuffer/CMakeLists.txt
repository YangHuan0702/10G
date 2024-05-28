add_library(gbSecond_minBuffer OBJECT mini_buffer_pool_manager.cpp)

SET(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:gbSecond_minBuffer> PARENT_SCOPE)