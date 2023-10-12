cmake_minimum_required(VERSION 3.21)

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

#
# Project details
#

project(
  "ej_2"
  VERSION 0.1.0
  LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

#
# Prevent building in the source directory
#

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

add_executable(${PROJECT_NAME} src/ej_2.cpp)

find_package(OpenCV REQUIRED)

message(STATUS "----------------------- ${OpenCV_INCLUDE_DIRS} ------------------------") 

target_include_directories(${PROJECT_NAME} PRIVATE
                              ${OpenCV_INCLUDE_DIRS}
                              ${HEADERS_DIR}
                           )

target_link_libraries(${PROJECT_NAME} PRIVATE 
                        ${OpenCV_LIBS}
                     )


