#include <string>
#include <iostream>

#include "OpenID.hpp"
#include "ExampleSettings.hpp"

using namespace OpenID;
using namespace OpenID::Examples;

bool getChoice(const std::string & str){
    while (true) {
        const auto input = getInput(str + " (y/n)");
        if (input == "y") {
            return true;
        } else if (input == "n") {
            return false;
        }

        std::cout << "Invalid input: " << input << '\n';
    }
}

void resendCode(const IDProvider & idProvider) {
    const auto choice = getChoice("Would you like to resend confirmation code?");
    if (choice) {
        idProvider.resendCode();
    }
}

void verifyUser(
    const IDProvider & idProvider
) {
    bool success = false;
    while (!success) {
        const auto confirmationCode = getInput("Enter confirmation code");
        try {
            idProvider.verifyUser(confirmationCode);
            success = true;
        } catch (std::runtime_error e) {
            std::cout << e.what() << '\n';
            std::cout << "Please try again!\n";
            resendCode(idProvider);
        }
    }
}

int main() {
    APIClient client;

    const auto settings = getSettings();
    
    const auto idProvider = IDProvider(settings);
    try {
        idProvider.signUpUser();
    } catch (std::runtime_error e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    verifyUser(idProvider);

    return 0;
}
