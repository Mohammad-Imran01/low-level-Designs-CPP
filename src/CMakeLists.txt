# Add subdirectories (modules/libraries)
add_subdirectory(logger)

# Common constants interface library
add_library(FILE_COMMON_CONST INTERFACE)
target_include_directories(FILE_COMMON_CONST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Add main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Logger
        FILE_COMMON_CONST
)
