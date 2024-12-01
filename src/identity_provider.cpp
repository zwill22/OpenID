#include "identity_provider.hpp"

#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeRequest.h>

using namespace Aws::Utils;
using namespace Aws::Client;
using namespace Aws::CognitoIdentityProvider;

namespace OpenBus {

ClientConfiguration setupClientConfig(const IDSettings & settings) {
    ClientConfiguration clientConfig;

    clientConfig.region = settings.clientRegion;
    clientConfig.appId = settings.clientID;
    
    return clientConfig;
}

struct IDProvider::IDProviderClient : public CognitoIdentityProviderClient {
    IDProviderClient(const IDSettings & settings) : CognitoIdentityProviderClient(setupClientConfig(settings)) {}
};

IDProvider::IDProvider(const IDSettings & idSettings ) : settings(idSettings) {
    this->idProviderClient = std::make_unique<IDProviderClient>(settings);
}

IDProvider::~IDProvider() {}

void IDProvider::signUpUser() const {
    Model::SignUpRequest request;
    request.AddUserAttributes(Model::AttributeType().WithName("email").WithValue(settings.emailAddress));
    request.SetUsername(settings.userID);
    request.SetPassword(settings.password);
    request.SetClientId(settings.clientID);
    auto outcome = idProviderClient->SignUp(request);

    if (outcome.IsSuccess()) {
        std::cout << "User " << settings.userID << " successfully signed up.\n";
    } else if (outcome.GetError().GetErrorType() == CognitoIdentityProviderErrors::USERNAME_EXISTS) {
        throw std::runtime_error("The username already exists. Please enter a different username.");
    } else if (!outcome.IsSuccess()) {
        throw std::runtime_error(
            "Error with CognitoIdentityProvider::SignUpRequest. "
            + outcome.GetError().GetMessage()
        );
    }
}

void IDProvider::verifyUser(const std::string & confirmationCode) const {
    Model::ConfirmSignUpRequest request;

    request.SetUsername(settings.userID);
    request.SetConfirmationCode(confirmationCode);
    request.SetClientId(settings.clientID);


    auto outcome = idProviderClient->ConfirmSignUp(request);

    if (outcome.IsSuccess()) {
        std::cout << "User verified.\n";
    } else {
        throw std::runtime_error(
            "Error with CognitoIdentityProvider::ConfirmSignUp. "
            + outcome.GetError().GetMessage()
        );
    }
}

void IDProvider::resendCode() const {
    Model::ResendConfirmationCodeRequest request;
    request.SetUsername(settings.userID);
    request.SetClientId(settings.clientID);
    
    auto outcome = idProviderClient->ResendConfirmationCode(request);

    if (!outcome.IsSuccess()) {
        throw std::runtime_error(
            "Error with CognitoIdentityProvider::ResendConfirmationCode. "
            + outcome.GetError().GetMessage()
        );
    }
}

} // namespace OpenBus
