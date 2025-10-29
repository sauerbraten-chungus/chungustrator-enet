#ifndef ENET_CLIENT_H
#define ENET_CLIENT_H

#include <fmt/core.h>
#include <enet/enet.h>

void RunENet(
    const char* game_server_address,
    int game_server_port
);

#endif
