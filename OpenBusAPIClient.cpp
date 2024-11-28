#include <iostream>
#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/ListUserPoolsRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>

using namespace Aws::Client;
using namespace Aws::Utils;
using namespace Aws::CognitoIdentityProvider;

Aws::String getInput(const std::string & str, const int streamSize = 64) {
    std::cout << str << ": ";
    std::string input;
    getline(std::cin, input);

    return input;
}

void check_outcome(
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

int main() {
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Logging::LogLevel::Debug;

    const auto userName = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto email = getInput("Enter E-mail address");
    constexpr auto clientID = "59lgg6i7hcnv8kma81rn4i7qbr";
    constexpr auto clientRegion = "eu-west-2";
    
    InitAPI(options);
    int result = 0;
    {
        ClientConfiguration clientConfig;
        clientConfig.region = clientRegion;
        clientConfig.appId = clientID;

        CognitoIdentityProviderClient cognitoClient(clientConfig);
        Model::SignUpRequest request;

        request.AddUserAttributes(Model::AttributeType().WithName("email").WithValue(email));
        request.SetUsername(userName);
        request.SetPassword(password);
        request.SetClientId(clientID);
        auto outcome = cognitoClient.SignUp(request);

        check_outcome(outcome, userName);

    }
    Aws::ShutdownAPI(options);

    return result;
}