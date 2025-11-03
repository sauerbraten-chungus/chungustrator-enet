#include "verification_code_service.h"
#include "enet_client.h"
#include <chrono>
#include <fmt/base.h>
#include <thread>

grpc::Status VerificationCodeService::SendVerificationCodes(
    grpc::ServerContext* context,
    const chungustrator_enet::VerificationCodeRequest* request,
    chungustrator_enet::VerificationCodeResponse* response
) {
    const auto& codes = request->codes();
    for (const auto& pair : codes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::thread([codes]{
            std::this_thread::sleep_for(std::chrono::seconds(10));
            RunENet("127.0.0.1", 28785);
        }).detach();

    response->set_msg("Received");
    return grpc::Status::OK;
}
