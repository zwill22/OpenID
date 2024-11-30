#include "identity_provider.hpp"
#include "api_client.hpp"

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
    OpenBus::APIClient client;
    const auto userName = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto email = getInput("Enter E-mail address");
    
    const auto idProvider = IDProvider(userName, password, email);
    try {
        idProvider.signUpUser();
    } catch (std::runtime_error e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    verifyUser(idProvider);

    return 0;
}
