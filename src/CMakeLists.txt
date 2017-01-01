cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT "ztl")
project (${PROJECT})

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

find_package (Threads)

add_subdirectory (network)
add_subdirectory (utils)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")
INCLUDE_DIRECTORIES("${BASEPATH}/contrib/googletest-src/googletest/include")
INCLUDE_DIRECTORIES("/home/lizhieffe/development/ztl/src/contrib/googletest-src/googletest/include")

set(source_files
    main.cc)

# GTEST related config.
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_SOURCE_DIR}/contrib/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/contrib/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/contrib/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_SOURCE_DIR}/contrib/googletest-src
                 ${CMAKE_SOURCE_DIR}/contrib/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
#  ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^
# /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\
#  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
#  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
#  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |


add_library(${PROJECT}_lib)
add_executable(${PROJECT} ${source_files})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# Generate extra compilation info used by YCM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

target_link_libraries(${PROJECT}_lib
                      network
                      utils
                      pthread)
target_link_libraries(${PROJECT}
                      ${PROJECT}_lib)

######################################
# Testing
######################################
if (test)
  enable_testing()
  add_executable(${PROJECT}_test ${source_files})
  target_link_libraries(${PROJECT}_test
                        ${PROJECT}_lib
                        network_test
                        gtest_main)
  add_test(NAME ${PROJECT}_test
          COMMAND ${PROJECT}_test)
endif()


