#include "proto/chungus.grpc.pb.h"
#include "proto/chungus.pb.h"
#include <fmt/core.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <string.h>
#include <enet/enet.h>
#include <grpcpp/grpcpp.h>
#include <string>

class ChungusRPC final : public chungus::ChungusEnet::Service {
  public:
    grpc::Status Hello(
      grpc::ServerContext* context,
      const chungus::Meow* request,
      chungus::Nya* response
    ) override {
      response->set_data("hello");
      return grpc::Status::OK;
    }
};

void RunServer() {
  std::string server_address = "0.0.0.0:50051";

  ChungusRPC service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  fmt::println("Server listening on {}", server_address);

  server->Wait();
}

ENetHost* RunENet() {
  if (enet_initialize() != 0)
  {
    fmt::print("An error occured while initializing ENet.\n");
    exit (EXIT_FAILURE);
  }
  atexit (enet_deinitialize);

  ENetHost* client;

  client = enet_host_create(NULL, 1, 2, 0, 0);
  if (client == nullptr)
  {
    fmt::print("An error occured while initializng an ENet client host.\n");
    exit (EXIT_FAILURE);
  }

  ENetAddress address;
  ENetEvent event;
  ENetPeer* peer;

  enet_address_set_host(&address, "127.0.0.1");
  address.port = 28785;

  peer = enet_host_connect(client, &address, 3, 0);
  if (peer == nullptr)
  {
    fmt::print("No available peers for initiating an ENet connection.\n");
    exit (EXIT_FAILURE);
  }

  if (enet_host_service(client, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT)
  {
    fmt::print("Connection to host succeeded.\n");
  }
  else
  {
    enet_peer_reset(peer);
    fmt::print("Connection to host has failed.\n");
    exit (EXIT_FAILURE);
  }
  enet_host_flush(client);

  const char data[] = "data\0bruh\0moment\0";
  ENetPacket* packet = enet_packet_create(data, sizeof(data), ENET_PACKET_FLAG_RELIABLE);

  fmt::print("Sending test packet to server\n");
  int packet_sent = enet_peer_send(peer, 2, packet);
  if (packet_sent != 0)
  {
    fmt::print("Boy what the hell\n");
  }
  else
  {
    fmt::print("yay\n");
  }
  enet_host_flush(client);

  return client;
}

int main()
{
  // ENetHost* client = RunENet();
  RunServer();
  // enet_host_destroy(client);
  return 0;
}
