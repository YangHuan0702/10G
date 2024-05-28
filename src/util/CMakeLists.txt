add_library(gbSecond_util OBJECT string_util.cpp)

set(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:gbSecond_util> PARENT_SCOPE)
