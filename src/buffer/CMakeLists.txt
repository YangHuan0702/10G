add_library(second_buffer OBJECT buffer_manager.cpp)

set(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:second_buffer> PARENT_SCOPE)
