/// An example C++ application which uses the C interface rather than C++ interface

#include "OpenAPIClient.h"

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

bool equal(const std::string & str1, const std::string & str2) {
    return (str1 == str2);
}


bool resend(const void* idProvider) {
    auto in = getInput("Verification failed, would you like to resend code? (y/n)");
    while (true) {
        if (equal(in, "y")) {
            const auto resendSuccess = resendCode(idProvider);
            if (!resendSuccess) {
                return true;
            } else {
                return false;
            }
        } else if (equal(in, "n")) {
            return true;
        } else {
            std::cout << "Invalid option: " << in << '\n';
            in = getInput("Would you like to resend code? (y/n)");
        }
    }
}

void printInfo(
    const std::string & userID,
    const std::string & password,
    const std::string & emailAddress,
    const std::string & clientRegion,
    const std::string & clientID
) {
    std::cout << std::string("=", 32) << '\n' << "User information:\n";
    std::cout << "Username: " << userID << '\n'; 
    std::cout << "Pasword: " << std::string("*", password.size()) << '\n'; 
    std::cout << "E-mail: " << emailAddress << '\n'; 
    std::cout << "Client Region: " << clientRegion << '\n'; 
    std::cout << "Client ID: " << clientID.substr(0, 24) << '\n'; 
}

int main() {
    //const std::string clientID = "59lgg6i7hcnv8kma81rn4i7qbr";
    //const std::string clientRegion = "eu-west-2"; 

    // ID settings, ensure these exist for the entirety of the program

    const auto userID = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto emailAddress = getInput("Enter E-mail address");
    const auto clientRegion = getInput("Enter Client region");
    const auto clientID = getInput("Enter Client ID");

    printInfo(userID, password, emailAddress, clientRegion, clientID);

    // Initialise API client
    const auto apiClient = initialiseOpenAPIClient();

    // Initialise ID Provider
    const auto idProvider = initialiseOpenIDProvider(
        userID.c_str(), password.c_str(), emailAddress.c_str(), clientRegion.c_str(), clientID.c_str()
    );
    if (idProvider == nullptr) {
        return 1;
    }

    // Attempt to sign up a user
    const auto signUpSuccess = signUpUser(idProvider);
    if (!signUpSuccess) {
        return 2;
    }

    // User verification and resend code on failure loop
    std::cout << "User signed-up successfully\n"
        << "Verification code e-mailed to: " << emailAddress << '\n';
    const auto code = getInput("Input Verification code");
    auto verifyUserSuccess = verifyUser(idProvider, code.c_str());
    while (!verifyUserSuccess) {
        const bool resendSuccess = resend(idProvider);
        if (!resendSuccess) {
            return 3;
        }
        const auto newCode = getInput("Reinput Verification code");
        verifyUserSuccess = verifyUser(idProvider, newCode.c_str());
    }

    std::cout << "User verified, requesting authentication credentials...\n";
    const auto authentication = authenticate(idProvider);
    if (authentication == nullptr) {
        return 4;
    }

    // TODO Expose authentication members

    std::cout << "User authenticated!\n";
    while (true) {
        const auto del = getInput("Delete profile? (y/n)");
        if (equal(del, "y")) {
            const auto deleteUserSuccess = deleteUser(idProvider, authentication);
            if (!deleteUserSuccess) {
                return 5;
            } else {
                std::cout << "User deleted\n";
                return 0;
            }
        } else if (equal(del, "n")) {
            std::cout << "User saved\n";
            return 0;
        } else {
            std::cout << "Invalid input: " << del << '\n';
        }
    }
}
