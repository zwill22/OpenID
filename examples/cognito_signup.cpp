#include "identity_provider.hpp"

#include <string>
#include <iostream>

std::string getInput(
    const std::string & str,
    const int streamSize = 64
    ) {
    std::cout << str << ": ";
    std::string input;
    getline(std::cin, input);

    return input;
}

int main() {
    const auto userName = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto email = getInput("Enter E-mail address");
    
    const auto idProvider = OpenBus::IDProvider(userName, password, email);

    idProvider.signUpUser();
}