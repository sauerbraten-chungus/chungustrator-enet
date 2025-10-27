cmake_minimum_required(VERSION 3.10)

project(chungustrator-enet)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)
find_package(grpc CONFIG REQUIRED)

add_executable(chungustrator-enet main.cpp proto/chungus.grpc.pb.cc proto/chungus.pb.cc)

target_include_directories(chungustrator-enet PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(chungustrator-enet PRIVATE unofficial::enet::enet fmt::fmt gRPC::grpc++)
