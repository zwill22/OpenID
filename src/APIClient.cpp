#include "APIClient.hpp"

#include <aws/core/Aws.h>

namespace OpenID {

struct APIClient::Options : public Aws::SDKOptions {};

APIClient::APIClient() : options(new Options()) {
    Aws::InitAPI(*options);
}

APIClient::~APIClient() {
    Aws::ShutdownAPI(*options);
}

} // namespace OpenID
