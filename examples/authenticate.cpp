#include <string>
#include <iostream>

#include "api_client.hpp"
#include "identity_provider.hpp"
#include "examples_settings.hpp"

using OpenBus::IDProvider;
using OpenBus::IDSettings;

int main() {
    OpenBus::APIClient client;

    const auto settings = OpenBusExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    idProvider.passwordAuth();

    return 0;
}
