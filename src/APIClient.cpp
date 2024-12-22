#include "APIClient.hpp"

#include <aws/core/Aws.h>
#include "error.hpp"

namespace OpenID {

struct APIClient::Options : public Aws::SDKOptions {};

APIClient::APIClient() : options(new Options()) {
    try {
        Aws::InitAPI(*options);
    } catch (const std::exception & e) {
        throw OpenIDError(e.what());
    }
}

APIClient::~APIClient() {
    try {
    Aws::ShutdownAPI(*options);
    } catch (const std::exception & e) {
        throw OpenIDError(e.what());
    }
}

} // namespace OpenID
