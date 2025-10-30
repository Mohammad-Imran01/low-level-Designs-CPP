add_library(lib_logger STATIC
    logger.cpp
    logger.h
)

target_include_directories(lib_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
