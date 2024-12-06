#include <string>
#include <iostream>

#include "OpenID.hpp"
#include "ExampleSettings.hpp"

using namespace OpenID;

int main() {
    APIClient client;

    const auto settings = OpenID::Examples::getSettings();
    
    auto idProvider = IDProvider(settings);
    auto auth = idProvider.passwordAuthenticate();

    idProvider.deleteUser(auth);

    return 0;
}
