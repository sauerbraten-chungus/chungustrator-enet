#include <fmt/core.h>
#include <enet/enet.h>

int main()
{  
  if (enet_initialize() != 0)
  {
    fmt::print("An error occured while initializing ENet.\n");
    return EXIT_FAILURE;
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

  peer = enet_host_connect(client, &address, 2, 0);
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
  }
  
  enet_host_destroy(client);
  return 0;
}
