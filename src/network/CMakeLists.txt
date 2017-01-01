SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/contrib/googletest-src/googletest/include")  

SET(network_src_files
    http_header.h
    http_header.cc)

SET(network_test_src_files
    http_header_test.cc)

ADD_LIBRARY(network ${network_src_files})
ADD_LIBRARY(network_test ${network_test_src_files})
