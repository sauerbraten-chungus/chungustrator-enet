#include "auth_code_service.h"
#include <fmt/core.h>
#include <grpcpp/server_builder.h>
#include <enet/enet.h>



void RunServer() {
    std::string server_address = "0.0.0.0:50051";

    AuthCodeService service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    fmt::println("Server listening on {}", server_address);

    server->Wait();
}

int main()
{
    if (enet_initialize() != 0)
    {
        fmt::print("An error occured when initializing ENet.\n");
    }
    RunServer();

    return 0;
}
