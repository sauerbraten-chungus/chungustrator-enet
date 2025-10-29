#ifndef AUTH_CODE_SERVICE_H
#define AUTH_CODE_SERVICE_H

#include "proto/chungustrator_enet.grpc.pb.h"
#include "proto/chungustrator_enet.pb.h"
#include <grpcpp/server_context.h>


class AuthCodeService final : public chungustrator_enet::AuthCodeService::Service {
public:
    grpc::Status SendAuthCodes(
        grpc::ServerContext* context,
        const chungustrator_enet::AuthCodeRequest* request,
        chungustrator_enet::AuthCodeResponse* response
    ) override;
};

#endif
