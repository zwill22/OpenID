#include "api_client.hpp"

#include <aws/core/Aws.h>

namespace OpenAPI {

struct APIClient::Options : public Aws::SDKOptions {};

APIClient::APIClient() : options(new Options()) {
    Aws::InitAPI(*options);
}

APIClient::~APIClient() {
    Aws::ShutdownAPI(*options);
}

} // namespace OpenAPI
