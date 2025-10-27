# Logger library name variable
set(LRUCache_LIB_NAME lruCache)

add_library(${LRUCache_LIB_NAME} STATIC lrucache.cpp )

# Make include directories available to consumers
target_include_directories(${LRUCache_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
