set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/contrib/googletest-src/googletest/include")  

set(utils_src_files
    socket_util.h
    socket_util.cc)

add_library(utils ${utils_src_files})
