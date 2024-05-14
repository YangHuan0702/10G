add_library(gbSecond_disk OBJECT disk_page_manager.cpp)

set(ALL_OBJECTS ${ALL_OBJECTS} $<TARGET_OBJECTS:gbSecond_disk> PARENT_SCOPE)
