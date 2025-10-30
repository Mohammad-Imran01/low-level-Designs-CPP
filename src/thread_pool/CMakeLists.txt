add_library(lib_threadpool STATIC
    thread_pool.cpp
    thread_pool.h
)

target_include_directories(lib_threadpool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
