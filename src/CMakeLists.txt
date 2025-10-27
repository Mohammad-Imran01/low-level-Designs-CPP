# Add subdirectories (modules/libraries)
add_subdirectory(logger)
add_subdirectory(lrucache)

# Common constants interface library
add_library(FILE_COMMON_CONST INTERFACE)
target_include_directories(FILE_COMMON_CONST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Add main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        FILE_COMMON_CONST
        Logger
        lruCache
)

# Include directories for main project
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/lrucache
        ${CMAKE_CURRENT_SOURCE_DIR}/logger
)
