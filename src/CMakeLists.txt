add_subdirectory(logger)
add_subdirectory(lrucache)
add_subdirectory(thread_pool)

add_executable(${PROJECT_NAME} 
    main.cpp 
    common/constants.h
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        lib_logger
        lib_lrucache
        lib_threadpool
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ${CMAKE_CURRENT_SOURCE_DIR}/logger
        ${CMAKE_CURRENT_SOURCE_DIR}/lrucache
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool
)
