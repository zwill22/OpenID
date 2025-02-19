#include "IdentityProvider.hpp"

#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeRequest.h>
#include <aws/cognito-idp/model/InitiateAuthRequest.h>
#include <aws/cognito-idp/model/RespondToAuthChallengeRequest.h>
#include <aws/cognito-idp/model/DeleteUserRequest.h>

#include "error.hpp"

using namespace Aws::Utils;
using namespace Aws::Client;
using namespace Aws::CognitoIdentityProvider;

namespace OpenID {

template <typename AuthenticationResult>
Authentication authenticateResults(const AuthenticationResult & result) {
    Authentication authResults;

    // Access token
    if (!result.AccessTokenHasBeenSet()) {
        throw OpenIDError("AccessToken not set");
    }
    authResults.accessToken = result.GetAccessToken();

    // Expiry time
    if (!result.ExpiresInHasBeenSet()) {
        throw OpenIDError("ExpiresIn time not set");
    }
    authResults.expiryTime = result.GetExpiresIn();

    // ID token
    if (!result.IdTokenHasBeenSet()) {
        throw OpenIDError("IDToken not set");
    }
    authResults.idToken = result.GetIdToken();
    
    // Refresh token
    if (!result.RefreshTokenHasBeenSet()) {
        throw OpenIDError("RefreshToken not set");
    }
    authResults.refreshToken = result.GetRefreshToken();

    // Token type
    if (!result.TokenTypeHasBeenSet()) {
        throw OpenIDError("TokenType not set");
    }
    authResults.tokenType = result.GetTokenType();

    return authResults;
}


template <typename Outcome, typename Request>
auto checkOutcome(
    Outcome outcome,
    Request request
) {
    if (!outcome.IsSuccess()) {
        throw OpenIDError(
            std::string(request.GetServiceRequestName()) + " Error: "
            + outcome.GetError().GetMessage() + " Thrown from OpenID"
        );
    }

    return outcome.GetResult();
}

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
    const auto outcome = idProviderClient->SignUp(request);

    checkOutcome(outcome, request);
}

void IDProvider::verifyUser(const std::string & confirmationCode) const {
    Model::ConfirmSignUpRequest request;

    request.SetUsername(settings.userID);
    request.SetConfirmationCode(confirmationCode);
    request.SetClientId(settings.clientID);

    const auto outcome = idProviderClient->ConfirmSignUp(request);
    checkOutcome(outcome, request);
}

void IDProvider::resendCode() const {
    Model::ResendConfirmationCodeRequest request;
    request.SetUsername(settings.userID);
    request.SetClientId(settings.clientID);
    
    const auto outcome = idProviderClient->ResendConfirmationCode(request);
    checkOutcome(outcome, request);
}

template <typename ResultType>
bool checkResult(const ResultType & result) {
    if (result.GetChallengeName() == Model::ChallengeNameType::NOT_SET) {
        if (result.GetSession() == "") {
            return true;
        }
    } else if (result.GetChallengeName() == Model::ChallengeNameType::NEW_PASSWORD_REQUIRED) {
        throw OpenIDError("New password required");
    }
    
    return false;
}

Authentication IDProvider::passwordAuthenticate() const {
    Model::InitiateAuthRequest request;

    request.SetAuthFlow(Model::AuthFlowType::USER_AUTH);
    request.AddAuthParameters("USERNAME", settings.userID);
    request.AddAuthParameters("PASSWORD", settings.userID);
    request.SetClientId(settings.clientID);

    const auto outcome = idProviderClient->InitiateAuth(request);

    const auto result = checkOutcome(outcome, request);

    if (checkResult(result)) {
        return authenticateResults(result.GetAuthenticationResult());
    }

    Model::RespondToAuthChallengeRequest selectChallengeRequest;
    selectChallengeRequest.SetChallengeName(result.GetChallengeName());
    selectChallengeRequest.SetClientId(settings.clientID);
    selectChallengeRequest.SetSession(result.GetSession());
    selectChallengeRequest.SetChallengeResponses({
        {"USERNAME", settings.userID},
        {"PASSWORD", settings.password},
        {"ANSWER", "PASSWORD"}
    });

    const auto selectChallengeOutcome = idProviderClient->RespondToAuthChallenge(selectChallengeRequest);
    const auto selectChallengeResult = checkOutcome(selectChallengeOutcome, selectChallengeRequest);
    if (checkResult(selectChallengeResult)) {
        return authenticateResults(selectChallengeResult.GetAuthenticationResult());
    }

    throw OpenIDError("User not authorised");
}

void IDProvider::deleteUser(const Authentication & authentication) const {
    Model::DeleteUserRequest request;

    request.SetAccessToken(authentication.accessToken);
    
    const auto outcome = idProviderClient->DeleteUser(request);

    checkOutcome(outcome, request);
}

} // namespace OpenID
