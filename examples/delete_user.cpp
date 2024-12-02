#include <string>
#include <iostream>

#include "api_client.hpp"
#include "identity_provider.hpp"
#include "examples_settings.hpp"

using namespace OpenBus;

int main() {
    OpenBus::APIClient client;

    const auto settings = OpenBusExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuthenticate();

    idProvider.deleteUser(auth);

    return 0;
}
