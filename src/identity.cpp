#include "identity.hpp"

#include <aws/core/Aws.h>

#include <aws/cognito-identity/CognitoIdentityClient.h>

using namespace Aws::Utils;
using namespace Aws::Client;
using namespace Aws::CognitoIdentity;

namespace OpenBus {

ClientConfiguration setupIdentityClientConfig(const IDSettings & settings) {
    ClientConfiguration clientConfig;

    clientConfig.region = settings.clientRegion;
    clientConfig.appId = settings.clientID;
    
    return clientConfig;
}

struct Identity::IDClient : public CognitoIdentityClient {
    IDClient(const IDSettings & settings) : CognitoIdentityClient(setupIdentityClientConfig(settings)) {}
};

Identity::Identity(const IDSettings & idSettings) : settings(idSettings), idClient(new IDClient(idSettings)) {}

Identity::~Identity() {};

} // namespace OpenBus
