#include <string>
#include <iostream>

#include "api_client.hpp"
#include "identity_provider.hpp"
#include "examples_settings.hpp"

using OpenAPI::APIClient;
using OpenAPI::IDProvider;
using OpenAPI::IDSettings;

void printRow(const int n = 64, const char c = '=') {
    std::cout << std::string(n, c) << '\n';
}

void printToken(const std::string & key, const std::string & value, const size_t truncate = 32) {
    if (value.size() > truncate) {
        std::cout << key << ":\t" << value.substr(0, truncate) << "...\n";
    } else {
        std::cout << key << ":\t" << value << '\n';
    }
}

void printAuthentication(const auto & auth) {
    printRow();
    std::cout << "Authentication result" << '\n';
    printRow();
    printToken("Access Token", auth.accessToken);
    std::cout << "Expiry time:\t" << auth.expiryTime << '\n';
    printToken("ID Token", auth.idToken);
    printToken("Refresh Token", auth.refreshToken);
    printToken("Token Type", auth.tokenType);
    printRow();
}

int main() {
    APIClient client;

    const auto settings = OpenAPIExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuthenticate();
    printAuthentication(auth);

    return 0;
}
