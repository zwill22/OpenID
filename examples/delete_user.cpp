#include <string>
#include <iostream>

#include "api_client.hpp"
#include "identity_provider.hpp"
#include "examples_settings.hpp"

using namespace OpenAPI;

int main() {
    APIClient client;

    const auto settings = OpenAPIExamples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuthenticate();

    idProvider.deleteUser(auth);

    return 0;
}
