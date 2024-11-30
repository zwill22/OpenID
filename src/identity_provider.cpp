#include "identity_provider.hpp"

#include "config.hpp"

#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/ListUserPoolsRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>

using namespace Aws::Utils;
using namespace Aws::Client;
using namespace Aws::CognitoIdentityProvider;

namespace OpenBus {

template <typename Outcome>
void checkOutcome(
    const Outcome & outcome,
    const Aws::String & userName
    ) {
    if (outcome.IsSuccess()) {
        std::cout << "The signup request for " << userName << " was successful.\n";
    }
    else if (outcome.GetError().GetErrorType() == CognitoIdentityProviderErrors::USERNAME_EXISTS) {
        throw std::runtime_error("The username already exists. Please enter a different username.");
    } else {
        std::cerr << "Error with CognitoIdentityProvider::SignUpRequest. "
        << outcome.GetError().GetMessage() << '\n';
        throw std::runtime_error("Error occurred during SignUpRequest");
    }
}

void signUpUser(
    const std::string & userName, 
    const std::string & password,
    const std::string & email
) { 

}

ClientConfiguration setupClientConfig() {
    ClientConfiguration clientConfig;

    clientConfig.region = Constants::clientRegion;
    clientConfig.appId = Constants::clientID;

    return clientConfig;
}

struct IDProvider::Options : public Aws::SDKOptions {};
struct IDProvider::Client : public CognitoIdentityProviderClient {
    Client() : CognitoIdentityProviderClient(setupClientConfig())
    {}
};

IDProvider::IDProvider(
    const std::string & userName,
    const std::string & userPassword,
    const std::string & userEmail
) : userID(userName),
    password(userPassword),
    emailAddress(userEmail),
    options(new Options())
{
    Aws::InitAPI(*options);
    this->client = std::make_unique<Client>();
}

IDProvider::~IDProvider() {
    Aws::ShutdownAPI(*options);
}

void IDProvider::signUpUser() const {
    Model::SignUpRequest request;
    request.AddUserAttributes(Model::AttributeType().WithName("email").WithValue(emailAddress));
    request.SetUsername(userID);
    request.SetPassword(password);
    request.SetClientId(Constants::clientID);
    auto outcome = client->SignUp(request);

    checkOutcome(outcome, userID);
}

void IDProvider::verifyUser(const std::string & confirmationCode) const {
    Model::ConfirmSignUpRequest request;

    request.SetUsername(userID);
    request.SetConfirmationCode(confirmationCode);
    request.SetClientId(Constants::clientID);


    auto outcome = client->ConfirmSignUp(request);

    if (outcome.IsSuccess()) {
        std::cout << "ConfirmSignup was Successful.\n";
        }
    else {
        std::cerr << "Error with CognitoIdentityProvider::ConfirmSignUp. "
                      << outcome.GetError().GetMessage() << '\n';

    }
}

} // namespace OpenBus
