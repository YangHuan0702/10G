add_library(gbSecond_buffer OBJECT buffer_manager.cpp lru_replace.cpp)

set(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:gbSecond_buffer> PARENT_SCOPE)
