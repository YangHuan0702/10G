add_subdirectory(buffer)

set(10G_lib
        second_buffer)

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