#include "OpenID.h"

#include <iostream>

#include "OpenID.hpp"

using namespace OpenID;

void *initialiseOpenIDClient() {
    try {
        APIClient* apiClient = new APIClient();

        return (void *) apiClient;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

IDSettings initialiseIDSettings(
    const char *userID,
    const char *password,
    const char *emailAddress,
    const char *clientRegion,
    const char *clientID    
) {
    IDSettings idSettings;
    idSettings.userID = userID;
    idSettings.password = password;
    idSettings.emailAddress = emailAddress;
    idSettings.clientRegion = clientRegion;
    idSettings.clientID = clientID;

    return idSettings;
}

void *initialiseOpenIDProvider(
    const char *userID,
    const char *password,
    const char *emailAddress,
    const char *clientRegion,
    const char *clientID
) {
    try {
        const auto idSettings = initialiseIDSettings(
            userID, password, emailAddress, clientRegion, clientID
        );

        IDProvider* idProvider = new IDProvider(idSettings);

        return (void *) idProvider;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

bool signUpUser(const void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        idProvider->signUpUser();
        return true;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool verifyUser(
    const void *idProviderPtr,
    const char *confirmationCode
) {
   try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;

        idProvider->verifyUser(confirmationCode);
        return true;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool resendCode(const void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        idProvider->resendCode();
        return true;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

void *authenticate(const void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;

        Authentication* authentication = new Authentication;
        *authentication = idProvider->passwordAuthenticate();

        return (void *) authentication;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

char* getAccessToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->accessToken.data();
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

int getExpiryTime(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->expiryTime;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 0;
    }
}

char* getIDToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->idToken.data();
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

char* getRefreshToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->refreshToken.data();
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

char* getTokenType(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->tokenType.data();
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }   
}

bool deleteUser(const void *idProviderPtr, const void *authenticationPtr)
{
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        const Authentication* authentication = (Authentication*) authenticationPtr;

        idProvider->deleteUser(*authentication);

        return true;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
