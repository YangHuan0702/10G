add_subdirectory(buffer)
add_subdirectory(disk)
add_subdirectory(task)
add_subdirectory(util)
add_subdirectory(minBuffer)

set(10G_lib
        gbSecond_buffer
        gbSecond_disk
        gbSecond_task
        gbSecond_util
        gbSecond_minBuffer
        )

find_package(Threads REQUIRED)

set(10G_THIRD_PARTY
        Threads::Threads
#        gflags::gflags
        )


add_library(10G STATIC ${ALL_OBJECTS} )

target_link_libraries(10G ${10G_lib} ${10G_THIRD_PARTY})

target_link_directories(10G PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)