cmake_minimum_required(VERSION 2.8)
project(binary_angle_measurement)

if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()
message(STATUS "Build configuration: ${CMAKE_BUILD_TYPE}")

set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib" CACHE PATH "Target directory for all libraries.")
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin" CACHE PATH "Target directory for all executables.")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(bam SHARED src/bam.c)

set_target_properties(bam PROPERTIES PUBLIC_HEADER "include/bam.h")

add_executable(BAMTest tests/bam_tests.c)
target_link_libraries(BAMTest bam)
