#include "auth_code_service.h"
#include "enet_client.h"

grpc::Status AuthCodeService::SendAuthCodes(
    grpc::ServerContext* context,
    const chungustrator_enet::AuthCodeRequest* request,
    chungustrator_enet::AuthCodeResponse* response
) {
    response->set_msg("Received");

    RunENet("127.0.0.1", 28785);

    return grpc::Status::OK;
}
