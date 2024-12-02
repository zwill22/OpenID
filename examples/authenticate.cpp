#include <string>
#include <iostream>

#include "api_client.hpp"
#include "identity_provider.hpp"
#include "examples_settings.hpp"

using OpenBus::IDProvider;
using OpenBus::IDSettings;

void print_row(const int n = 64, const char c = '=') {
    std::cout << std::string(n, c) << '\n';
}

void print_token(const std::string & key, const std::string & value, const size_t truncate = 32) {
    if (value.size() > truncate) {
        std::cout << key << ":\t" << value.substr(0, truncate) << "...\n";
    } else {
        std::cout << key << ":\t" << value << '\n';
    }
}

int main() {
    OpenBus::APIClient client;

    const auto settings = OpenBusExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuth();

    print_row();
    std::cout << "Authentication result" << '\n';
    print_row();
    print_token("Access Token", auth.accessToken);
    std::cout << "Expiry time:\t" << auth.expiryTime << '\n';
    print_token("ID Token", auth.idToken);
    print_token("Refresh Token", auth.refreshToken);
    print_token("Token Type", auth.tokenType);
    print_row();

    return 0;
}
