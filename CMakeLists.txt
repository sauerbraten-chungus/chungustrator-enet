cmake_minimum_required(VERSION 3.10)

project(chungustrator-enet)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)
find_package(grpc CONFIG REQUIRED)

add_executable(chungustrator-enet src/main.cpp proto/chungustrator_enet.grpc.pb.cc proto/chungustrator_enet.pb.cc src/enet_client.cpp src/verification_code_service.cpp)

target_include_directories(chungustrator-enet PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(chungustrator-enet PRIVATE unofficial::enet::enet fmt::fmt gRPC::grpc++)
