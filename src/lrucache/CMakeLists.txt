add_library(lib_lrucache STATIC
    lrucache.cpp
    lrucache.h
)

target_include_directories(lib_lrucache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
