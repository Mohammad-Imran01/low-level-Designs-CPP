# Add subdirectories (modules/libraries)
add_subdirectory(logger)

# Add main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link Logger library
target_link_libraries(${PROJECT_NAME} PRIVATE Logger)
