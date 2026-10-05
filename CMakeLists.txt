cmake_minimum_required(VERSION 3.24)
project(vllmcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

enable_testing()

# ---- Eigen (header-only, fetched and pinned) ---------------------------------
include(FetchContent)
set(EIGEN_BUILD_DOC       OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING         OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  Eigen3
  URL      https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
  URL_HASH SHA256=8586084f71f9bde545ee7fa6d00288b264a2b7ac3607b974e54d13e7162c1c72
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(Eigen3)

# ---- vllmcpp -----------------------------------------------------------------
# INTERFACE while there is no implementation yet. Phase 1 turns it into a STATIC
# library by adding sources here.
# add_library(vllmcpp INTERFACE)
add_library(vllmcpp STATIC src/ops.cpp)
target_include_directories(vllmcpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(vllmcpp INTERFACE Eigen3::Eigen)
target_compile_features(vllmcpp INTERFACE cxx_std_20)

# ---- demo --------------------------------------------------------------------
add_executable(vllmcpp_demo src/main.cpp)
target_link_libraries(vllmcpp_demo PRIVATE vllmcpp)

# ---- tests -------------------------------------------------------------------
# Each phase adds one target. Tests use tests/check.h, not <cassert> — assert is
# compiled out under NDEBUG, which is the default build type here.
function(vllm_add_test name)
  add_executable(${name} tests/${name}.cpp)
  target_link_libraries(${name} PRIVATE vllmcpp)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

vllm_add_test(test_smoke)
vllm_add_test(test_ops)

