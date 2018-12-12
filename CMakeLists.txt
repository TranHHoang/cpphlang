cmake_minimum_required(VERSION 3.2)
project(HLang)

#find_package(LLVM REQUIRED CONFIG)
#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(HLANG_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(HLANG_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
#set(DIVISIBLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${HLANG_INSTALL_INCLUDE_DIR})
# llvm
#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})
#llvm_map_components_to_libnames(llvm_libs support core irreader)
#include_directories(${HLANG_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)