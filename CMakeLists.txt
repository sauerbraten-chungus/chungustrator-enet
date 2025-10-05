cmake_minimum_required(VERSION 3.10)

project(chungustrator-enet)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)

add_executable(chungustrator-enet main.cpp)

target_link_libraries(chungustrator-enet PRIVATE unofficial::enet::enet fmt::fmt)
