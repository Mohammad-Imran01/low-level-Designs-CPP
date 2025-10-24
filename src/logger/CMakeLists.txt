# Logger library
set(LOGGER_LIB_NAME Logger)

add_library(${LOGGER_LIB_NAME} STATIC logger.cpp)

# Make include directories available to consumers
target_include_directories(${LOGGER_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
