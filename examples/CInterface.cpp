/// An example C++ application which uses the C interface rather than C++ interface

#include "OpenID.h"

#include <string>
#include <iostream>

std::string getInput(
    const std::string & str
) {
    std::cout << str << ": ";
    std::string input;
    std::cin >> input;

    return input;
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

void printMenu() {
    constexpr int n = 32;

    std::cout << std::string(2 * n, '=') << '\n' << "OpenID Interface\n";
    std::cout << "Choose option:" << '\n';
    std::cout << "1:\tSign-Up" << '\n';
    std::cout << "2:\tVerify User" << '\n';
    std::cout << "3:\tResend Verification Code" << '\n';
    std::cout << "4:\tRequest Authentication" << '\n';
    std::cout << "5:\tPrint Authentication" << '\n';
    std::cout << "6:\tDelete User" << '\n';
    std::cout << "0:\tExit" << '\n';
    std::cout << std::string(2 * n, '=') << '\n';
}

void signUp(const void * idProvider, const std::string & emailAddress) {
    if(signUpUser(idProvider)) {
    std::cout << "User signed-up successfully\n"
        << "Verification code e-mailed to: " << emailAddress << '\n';
    } else {
        std::cerr << "OpenID Sign-up error, please try again..." << '\n';
    }
}

void verify(const void * idProvider) {
    
    const std::string code = getInput("Input verification code");

    if (verifyUser(idProvider, code.c_str())) {
        std::cout << "User successfully verified" << '\n';
    } else {
        std::cerr << "User verification failure" << '\n';
    }
}

void resend(const void * idProvider) {
    if (resendCode(idProvider)) {
        std::cout << "New verification code sent" << '\n';
    } else {
        std::cerr << "Resend verification code failure" << '\n';
    }
}

bool requestAuthentication(void * idProvider, void * authentication) {
    if (authenticate(authentication, idProvider)) {
        std::cout << "User authenticated" << '\n';
        return true;
    } else {
        std::cerr << "User authentication failure" << '\n';
        return false;
    }
}

void printAuthentication(void * authentication) {
    std::cout << "Acquiring tokens..." << '\n';
    // Get authentication credentials from pointer
    const auto accessToken = getAccessToken(authentication);
    if (accessToken == nullptr) {
        std::cerr << "OpenID AccessToken retrieval error" << '\n';
        return;
    }
    const auto expiryTime = getExpiryTime(authentication);
    if (expiryTime == 0) {
        std::cerr << "OpenID expiryTime retrieval error" << '\n';
        return;
    }
    const auto idToken = getIDToken(authentication);
    if (idToken == nullptr) {
        std::cerr << "OpenID IDToken retrieval error" << '\n';
        return;
    }
    const auto refreshToken = getRefreshToken(authentication);
    if (refreshToken == nullptr) {
        std::cerr << "OpenID RefreshToken retrieval error" << '\n';
        return;
    }
    const auto tokenType = getTokenType(authentication);
    if (tokenType == nullptr) {
        std::cerr << "OpenID TokenType retrieval error" << '\n';
        return;
    }

    printAuthentication(accessToken, expiryTime, idToken, refreshToken, tokenType);
}

void requestDeletion(void * idProvider, void * authentication) {
    char del;
    std::cout << "Delete profile? (y/n): ";
    std::cin >> del;
    std::cout << '\n';
    switch (del)
    {
    case 'y':
        if(deleteUser(idProvider, authentication)) {
            std::cout << "User successfully deleted" << '\n';
        } else {
            std::cerr << "User deletion error" << '\n';
        }
        break;
    case 'n':
        std::cout << "User deletion cancelled" << '\n';
        break;
    default:
        std::cout << "Invalid input" << '\n';
        break;
    }
}

int main() {
    std::cout << "Welcome to the OpenID Interface" << '\n';
    const auto clientRegion = getInput("Enter Client region");
    const auto clientID = getInput("Enter Client ID");

    // ID settings, ensure these exist for the entirety of the program
    const auto userID = getInput("Enter User Name");
    const auto password = getInput("Enter password");
    const auto emailAddress = getInput("Enter E-mail address");

    printInfo(userID, password, emailAddress, clientRegion, clientID);

    // Initialise API client
    void * apiClient = alloca(openIDClientSize());
    {
        const auto success = initialiseOpenIDClient(apiClient);
        if (!success) {
            std::cerr << "OpenID Client initialisation failure" << '\n';
            return 1;
        }
    }

    // Initialise ID Provider
    void * idProvider = alloca(idProviderSize());
    {
        const auto success = initialiseOpenIDProvider(
            idProvider,
            userID.c_str(),
            password.c_str(),
            emailAddress.c_str(),
            clientRegion.c_str(),
            clientID.c_str()
        );
        if (!success) {
            std::cerr << "OpenID IDProvider initialisation failure" << '\n';
            return 1;
        }
    }

    void * authentication = alloca(authenticationSize());
    bool authenticated = false;

    bool menu = true;
    while (menu)
    {
        printMenu();
        char choice;
        std::cout << "Enter Choice: ";
        std::cin >> choice;
        std::cout << '\n';
        switch (choice)
        {
        case '1':
            signUp(idProvider, emailAddress);
            break;
        case '2':
            verify(idProvider);
            break;
        case '3':
            resend(idProvider);
            break;
        case '4':
            authenticated = requestAuthentication(idProvider, authentication);
            break;
        case '5':
            if (authenticated) {
                printAuthentication(authentication);
            } else {
                std::cout << "User not authenticated" << '\n';
            }
            break;
        case '6':
            if (authenticated) {
                requestDeletion(idProvider, authentication);
            } else {
                std::cout << "User not authenticated" << '\n';
            }
            break;
        case '0':
            std::cout << "Shutting down OpenID interface..." << '\n';
            menu = false;
            break;
        default:
            std::cout << "Invalid choice: " << choice << '\n';
            break;
        }
    }

    if (!uninitialiseOpenIDProvider(idProvider)) {
        std::cerr << "OpenID IDProvider uninitialisation error" << '\n';
        return 2;
    }

    if (!uninitialiseOpenIDClient(apiClient)) {
        std::cerr << "OpenID Client uninitialisation error" << '\n';
        return 2;
    }

    std::cout << "Shut down successful, goodbye." << '\n';
    
    return 0;
}
