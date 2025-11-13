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
    RunServer();

    ENetAddress server_address;
    ENetHost *server;
    server_address.host = ENET_HOST_ANY;
    server_address.port = 1234;

    server = enet_host_create(&server_address, 32, 2, 0, 0);
    ENetEvent event;
    while(enet_host_service(server, &event, 100) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                fmt::println("A new client connected from %x:%u.\n",
                    event.peer->address.host,
                    event.peer->address.port
                );
                /* Store any relevant client information here. */
                // event.peer->data = "Client information";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                fmt::println("A packet of length %u containing %s was received from %s on channel %u.\n",
                    event.packet->dataLength,
                    event.packet->data,
                    event.peer->data,
                    event.channelID
                );
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                fmt::println("%s disconnected.", event.peer->data);
                /* Reset the peer's client information. */
                event.peer -> data = NULL;
                break;
            case ENET_EVENT_TYPE_NONE:
                fmt::println("idk bruh");
        }
    }

    return 0;
}
