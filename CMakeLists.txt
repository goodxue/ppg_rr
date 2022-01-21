cmake_minimum_required(VERSION 2.8.3)
project(ppg_rr)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${EIGEN3_INCLUDE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build )

add_executable(ppg_rr
        src/main.cpp
        src/ppg_rr_cpp.cpp

	)
target_link_libraries(ppg_rr
  ${PROJECT_SOURCE_DIR}/include
)
