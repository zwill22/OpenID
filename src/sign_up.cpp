#include "sign_up.hpp"

#include "config.hpp"

#include <iostream>
#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/ListUserPoolsRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>

using namespace Aws::Client;
using namespace Aws::CognitoIdentityProvider;

namespace OpenBus {

void checkOutcome(
    const Model::SignUpOutcome & outcome,
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
    ClientConfiguration clientConfig;
    clientConfig.region = Constants::clientRegion;
    clientConfig.appId = Constants::clientID;
    
    CognitoIdentityProviderClient cognitoClient(clientConfig);
    Model::SignUpRequest request;
    request.AddUserAttributes(Model::AttributeType().WithName("email").WithValue(email));
    request.SetUsername(userName);
    request.SetPassword(password);
    request.SetClientId(Constants::clientID);
    auto outcome = cognitoClient.SignUp(request);

    checkOutcome(outcome, userName);
}

} // namespace OpenBus
