#include "OpenID.h"

#include <iostream>

#include "OpenID.hpp"

using namespace OpenID;

bool initialiseOpenIDClient(void* openIDClient) {
    try {
        new (openIDClient) APIClient();
        return true;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
bool uninitialiseOpenIDClient(void* openIDClient) {
    try {
        const APIClient* apiClient = (APIClient*) openIDClient;

        apiClient->~APIClient();

        return true;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

size_t openIDClientSize() {
    return sizeof(APIClient);
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

bool initialiseOpenIDProvider(
    void * idProvider,
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

        new (idProvider) IDProvider(idSettings);
        return true;
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
bool uninitialiseOpenIDProvider(void* idProvider) {
    try {
        const IDProvider* identityProvider = (IDProvider*) idProvider;

        identityProvider->~IDProvider();

        return true;
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

size_t idProviderSize() {
    return sizeof(IDProvider);
}

bool signUpUser(const void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        idProvider->signUpUser();
        return true;
    } catch (const OpenIDError & e) {
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
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool resendCode(const void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        idProvider->resendCode();
        return true;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

bool authenticate(void * authentication, void *idProviderPtr) {
    try {
        const IDProvider* idProvider = (IDProvider*) idProviderPtr;
        Authentication* authenticator = (Authentication*) authentication;
        *authenticator = idProvider->passwordAuthenticate();

        return true;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}

size_t authenticationSize() {
    return sizeof(Authentication);
}

char* getAccessToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        char* val = authentication->accessToken.data();
        return val;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

int getExpiryTime(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->expiryTime;
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 0;
    }
}

char* getIDToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->idToken.data();
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

char* getRefreshToken(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->refreshToken.data();
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return nullptr;
    }
}

char* getTokenType(void * authenticationPtr) {
    try {
        Authentication* authentication = (Authentication*) authenticationPtr;
        return authentication->tokenType.data();
    } catch (const OpenIDError & e) {
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
    } catch (const OpenIDError & e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
