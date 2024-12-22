#include <string>
#include <iostream>

#include "OpenID.hpp"
#include "ExampleSettings.hpp"

using OpenID::APIClient;
using OpenID::IDProvider;
using OpenID::IDSettings;

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

void printAuthentication(const OpenID::Authentication & auth) {
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

    const auto settings = OpenID::Examples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuthenticate();
    printAuthentication(auth);

    return 0;
}
