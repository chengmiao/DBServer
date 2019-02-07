cmake_minimum_required(VERSION 2.8)
project(dbserver)

set (CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_FLAGS "-std=c++11")

include_directories(${CMAKE_SOURCE_DIR}/opt/lua ${CMAKE_SOURCE_DIR}/opt/sol2)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(main main.cpp)
target_link_libraries(main liblua.a)