#include "identity_provider.hpp"

#include <string>
#include <iostream>

using OpenBus::IDProvider;

std::string getInput(
    const std::string & str,
    const int streamSize = 64
    ) {
    std::cout << str << ": ";
    std::string input;
    getline(std::cin, input);

    return input;
}

void signUp(const IDProvider & idProvider) {
    // Signup
    bool success = false;
    while (!success) {
        try {
            idProvider.signUpUser();
            success = true;
        } catch (std::runtime_error e) {
            std::cout << e.what() << '\n';
            std::cout << "Please try again!\n";
        }
    }
}

void verifyUser(
    const IDProvider & idProvider,
    const std::string & confirmationCode
) {
    bool success = false;
    while (!success) {
        try {
            idProvider.verifyUser(confirmationCode);
            success = true;
        } catch (std::runtime_error e) {
            std::cout << e.what() << '\n';
            std::cout << "Please try again!\n";
        }
    }
}

int main() {
    const auto userName = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto email = getInput("Enter E-mail address");
    
    const auto idProvider = IDProvider(userName, password, email);
    signUp(idProvider);

    const auto confirmationCode = getInput("Enter confirmation code");
    verifyUser(idProvider, confirmationCode);
}
