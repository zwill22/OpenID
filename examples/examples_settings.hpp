#ifndef OPEN_BUS_EXAMPLES_GET_SETTINGS_HPP
#define OPEN_BUS_EXAMPLES_GET_SETTINGS_HPP

#include <iostream>
#include <string>

#include "identity.hpp"

namespace OpenBusExamples {

std::string getInput(
    const std::string & str,
    const int streamSize = 64
) {
    std::cout << str << ": ";
    std::string input;
    getline(std::cin, input);

    return input;
}

OpenBus::IDSettings getSettings() {
    OpenBus::IDSettings settings;
    settings.clientID = "59lgg6i7hcnv8kma81rn4i7qbr";
    settings.clientRegion = "eu-west-2";
    settings.userID = getInput("Enter User Name");
    settings.password = getInput("Enter password");
    settings.emailAddress = getInput("Enter E-mail address");

    return settings;
}

}

#endif // OPEN_BUS_EXAMPLES_GET_SETTINGS_HPP