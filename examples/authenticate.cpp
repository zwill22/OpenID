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

int main() {
    OpenBus::APIClient client;

    const auto settings = OpenBusExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuth();

    print_row();
    std::cout << "Authentication result: " << '\n';
    print_row();
    for (const auto & [k, v] : auth) {
        if (v.size() > 32) {
            std::cout << k << ":\t" << v.substr(0, 32) << "...\n";
        } else {
            std::cout << k << ":\t" << v << '\n';
        }
    }
    print_row();

    return 0;
}
