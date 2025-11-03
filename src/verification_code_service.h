#ifndef VERIFICATION_CODE_SERVICE_H
#define VERIFICATION_CODE_SERVICE_H

#include "proto/chungustrator_enet.grpc.pb.h"
#include "proto/chungustrator_enet.pb.h"
#include <grpcpp/server_context.h>


class VerificationCodeService final : public chungustrator_enet::VerificationCodeService::Service {
public:
    grpc::Status SendVerificationCodes(
        grpc::ServerContext* context,
        const chungustrator_enet::VerificationCodeRequest* request,
        chungustrator_enet::VerificationCodeResponse* response
    ) override;
};

#endif
