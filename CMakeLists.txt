cmake_minimum_required(VERSION 2.8)
project(dbserver)

set (CMAKE_CXX_COMPILER /usr/local/bin/g++)
set (CMAKE_C_COMPILER /usr/bin/gcc)
set (CMAKE_CXX_FLAGS "-std=c++14 -ldl -lpthread")
set (CMAKE_C_FLAGS "-fPIC")
#add_compile_options(-std=c++14)
#add_compile_options(-ldl)

add_definitions(-DASIO_STANDALONE)

include_directories(${CMAKE_SOURCE_DIR}/opt/lua ${CMAKE_SOURCE_DIR}/opt/sol2 ${CMAKE_SOURCE_DIR}/opt/lua-protobuf ${CMAKE_SOURCE_DIR}/opt/asio/asio/include ${CMAKE_SOURCE_DIR}/opt/protobuf_linux/include
                    ${CMAKE_SOURCE_DIR}/proto/src)

link_directories(${CMAKE_SOURCE_DIR}/lib ${CMAKE_SOURCE_DIR}/opt/protobuf_linux/lib ${CMAKE_SOURCE_DIR}/proto)

#add_library(pb SHARED ${CMAKE_SOURCE_DIR}/opt/lua-protobuf/pb.c)
add_executable(main main.cpp)
target_link_libraries(main liblua.a)

#add_subdirectory(${CMAKE_SOURCE_DIR}/proto)

file(GLOB PROTO_SRCS ${CMAKE_SOURCE_DIR}/proto/src/*.cc)	
file(GLOB PROTO_HDRS ${CMAKE_SOURCE_DIR}/proto/src/*.h)
	
add_library(proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})
SET_TARGET_PROPERTIES (proto PROPERTIES OUTPUT_NAME "proto")

add_executable(client Client.cpp)
target_link_libraries(client proto protobuf)
