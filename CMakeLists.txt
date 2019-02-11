cmake_minimum_required(VERSION 2.8)
project(dbserver)

set (CMAKE_CXX_COMPILER /usr/local/bin/g++)
set (CMAKE_CXX_FLAGS "-std=c++14 -ldl -lpthread")
set (CMAKE_C_FLAGS "-fPIC")
#add_compile_options(-std=c++14)
#add_compile_options(-ldl)

add_definitions(-DASIO_STANDALONE)

include_directories(${CMAKE_SOURCE_DIR}/opt/lua ${CMAKE_SOURCE_DIR}/opt/sol2 ${CMAKE_SOURCE_DIR}/opt/lua-protobuf ${CMAKE_SOURCE_DIR}/opt/asio/asio/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

#add_library(pb SHARED ${CMAKE_SOURCE_DIR}/opt/lua-protobuf/pb.c)
add_executable(main main.cpp)
target_link_libraries(main liblua.a)