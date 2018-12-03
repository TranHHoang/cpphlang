cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(HLANG_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(HLANG_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
#set(DIVISIBLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${HLANG_INSTALL_INCLUDE_DIR})
include_directories(${HLANG_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


