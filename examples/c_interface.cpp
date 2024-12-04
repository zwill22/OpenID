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
            return resendCode(idProvider);
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
    const std::string & clientID,
    const int n = 32
) {
    std::cout << std::string(2 * n, '=') << '\n' << "User information:\n";
    std::cout << "Username:\t" << userID << '\n'; 
    std::cout << "Pasword:\t" << std::string(password.size(), '*') << '\n'; 
    std::cout << "E-mail:\t\t" << emailAddress << '\n'; 
    std::cout << "Client Region:\t" << clientRegion << '\n'; 
    std::cout << "Client ID:\t" << clientID.substr(0, n) << '\n'; 
    std::cout << std::string(2 * n, '=') << '\n';
}

void printAuthentication(
    const std::string & accessToken,
    const int expiryTime,
    const std::string & idToken,
    const std::string & refreshToken,
    const std::string & tokenType,
    const int n = 32
) {
    std::cout << std::string(2 * n, '=') << '\n' << "Authentication:\n";
    std::cout << "Access Token:\t" << accessToken.substr(0, n) << '\n'; 
    std::cout << "Expiry Time:\t" << expiryTime << '\n'; 
    std::cout << "ID Token:\t" << idToken.substr(0, n) << '\n'; 
    std::cout << "Refresh Token:\t" << refreshToken.substr(0, n) << '\n'; 
    std::cout << "Token Type:\t" << tokenType << '\n'; 
    std::cout << std::string(2 * n, '=') << '\n';
}

int main() {
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
            return 2;
        }
        const auto newCode = getInput("Reinput Verification code");
        verifyUserSuccess = verifyUser(idProvider, newCode.c_str());
    }

    std::cout << "User verified, requesting authentication credentials...\n";
    auto authentication = authenticate(idProvider);
    if (authentication == nullptr) {
        return 1;
    }

    std::cout << "Acquiring tokens..." << '\n';
    // Get authentication credentials from pointer
    const auto accessToken = getAccessToken(authentication);
    if (accessToken == nullptr) {
        return 1;
    }
    const auto expiryTime = getExpiryTime(authentication);
    if (expiryTime == 0) {
        return 1;
    }
    const auto idToken = getIDToken(authentication);
    if (idToken == nullptr) {
        return 1;
    }
    const auto refreshToken = getRefreshToken(authentication);
    if (refreshToken == nullptr) {
        return 1;
    }
    const auto tokenType = getTokenType(authentication);
    if (tokenType == nullptr) {
        return 1;
    }

    std::cout << "User authenticated!\n";
    printAuthentication(accessToken, expiryTime, idToken, refreshToken, tokenType);

    while (true) {
        const auto del = getInput("Delete profile? (y/n)");
        if (equal(del, "y")) {
            const auto deleteUserSuccess = deleteUser(idProvider, authentication);
            if (!deleteUserSuccess) {
                return 2;
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
