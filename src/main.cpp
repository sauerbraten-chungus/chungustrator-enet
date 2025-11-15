#include "verification_code_service.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <grpcpp/server_builder.h>
#include <enet/enet.h>

void print_packet_data(ENetPacket* packet) {
    uint8_t *buffer = packet->data;

    uint8_t flag = *buffer++;
    std::string test = std::string(reinterpret_cast<char*>(buffer));

    fmt::println("flag: {} string: {}", flag, test);
}

void RunServer() {
    std::string server_address = "0.0.0.0:50051";

    VerificationCodeService service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    fmt::println("Server listening on {}", server_address);

    server->Wait();
}

int main() {
    if (enet_initialize() != 0) {
        fmt::println("An error occured when initializing ENet.");
    }
    // RunServer();

    ENetAddress address;
    ENetHost *host;
    address.host = ENET_HOST_ANY;
    address.port = 30000;

    host = enet_host_create(&address, 32, 2, 0, 0);
    if (host == nullptr) {
        fmt::println("An error occurred while creating the ENet server host.");
        return 1;
    }
    fmt::println("ENet server listening on port {}", address.port);
    fmt::println("Waiting for connections...");

    ENetEvent event;
    while(enet_host_service(host, &event, 1000) >= 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                fmt::println("awesome");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                fmt::println("Received packet");
                print_packet_data(event.packet);
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                fmt::println("Client disconnected.");
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }

    enet_host_destroy(host);
    enet_deinitialize();

    return 0;
}
