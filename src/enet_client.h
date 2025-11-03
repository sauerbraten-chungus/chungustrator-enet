#ifndef ENET_CLIENT_H
#define ENET_CLIENT_H

#include <fmt/core.h>
#include <enet/enet.h>
#include <google/protobuf/map.h>
#include <string>

void RunENet(
    const char* game_server_address,
    int game_server_port,
    std::string buffer
);

#endif
