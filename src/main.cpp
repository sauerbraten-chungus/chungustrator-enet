#include "verification_code_service.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <grpcpp/server_builder.h>
#include <enet/enet.h>



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
        fmt::print("An error occured when initializing ENet.\n");
    }
    // RunServer();

    ENetAddress server_address;
    ENetHost *server;
    server_address.host = ENET_HOST_ANY;
    // enet_address_set_host(&server_address, "127.0.0.1");
    server_address.port = 30000;

    server = enet_host_create(&server_address, 32, 2, 0, 0);
    if (server == nullptr) {
        fmt::println("An error occurred while creating the ENet server host.");
        return 1;
    }
    fmt::println("ENet server listening on {}:{}", server_address.host, server_address.port);
    fmt::println("Waiting for connections...");

    ENetEvent event;
    while(true) {
        int result = enet_host_service(server, &event, 1000);
        if (result < 0) {
            fmt::println("Error in enet_host_service");
            break;
        }

        if (result > 0) {
            fmt::println("Event received: type={}", (int)event.type);
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    fmt::println("awesome");
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    fmt::println("Received packet");
                    enet_packet_destroy (event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    fmt::println("Client disconnected.");
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
            }
        }
    }
    enet_host_destroy(server);
    enet_deinitialize();

    return 0;
}
