#include "identity_provider.hpp"

#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeRequest.h>
#include <aws/cognito-idp/model/InitiateAuthRequest.h>
#include <aws/cognito-idp/model/RespondToAuthChallengeRequest.h>

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

AuthenticationResult IDProvider::passwordAuthenticate() const {
    Model::InitiateAuthRequest request;

    request.SetAuthFlow(Model::AuthFlowType::USER_AUTH);
    request.AddAuthParameters("USERNAME", settings.userID);
    request.AddAuthParameters("PASSWORD", settings.userID);
    request.SetClientId(settings.clientID);

    auto outcome = idProviderClient->InitiateAuth(request);

    if (!outcome.IsSuccess()) {
        throw std::runtime_error(
            "Error with CognitoIdentityProvider::InitiateAuth"
            + outcome.GetError().GetMessage()
        );
    }

    const auto result = outcome.GetResult();

    Model::RespondToAuthChallengeRequest selectChallengeRequest;
    selectChallengeRequest.SetChallengeName(result.GetChallengeName());
    selectChallengeRequest.SetClientId(settings.clientID);
    selectChallengeRequest.SetSession(result.GetSession());
    selectChallengeRequest.SetChallengeResponses({
        {"USERNAME", settings.userID},
        {"PASSWORD", settings.password},
        {"ANSWER", "PASSWORD"}
    });

    auto selectChallengeOutcome = idProviderClient->RespondToAuthChallenge(selectChallengeRequest);

    if (!selectChallengeOutcome.IsSuccess()) {
        throw std::runtime_error(
            "Error with CognitoIdentityProvider::RespondToAuthChallenge\n"
            + selectChallengeOutcome.GetError().GetMessage()
        );
    }

    const auto selectChallengeResult = selectChallengeOutcome.GetResult();
    if (selectChallengeResult.GetChallengeName() == Model::ChallengeNameType::NOT_SET) {
        if (selectChallengeResult.GetSession() == "") {
            return getResults(selectChallengeResult.GetAuthenticationResult());
        } else {
            throw std::runtime_error("Session provided - additional authorisation response expected");
        }
    } else if (selectChallengeResult.GetChallengeName() == Model::ChallengeNameType::NEW_PASSWORD_REQUIRED) {
        throw std::runtime_error("New password required");
    } else {
        throw std::runtime_error("Unknown additional challenge requested");
    }
}

} // namespace OpenBus
