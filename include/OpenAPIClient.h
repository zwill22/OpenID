#ifndef OPEN_API_C_INTERFACE_H
#define OPEN_API_C_INTERFACE_H

#include <stdbool.h>

// C-header for OpenAPIClient library

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


void* initialiseOpenAPIClient();

void* initialiseOpenIDProvider(
    const char * userID,
    const char * password,
    const char * emailAddress,
    const char * clientRegion,
    const char * clientID
);

bool signUpUser(const void * idProviderPtr);
bool verifyUser(const void * idProviderPtr, const char * confirmationCode);
bool resendCode(const void * idProviderPtr);

void* authenticate(const void * idProviderPtr);

bool deleteUser(const void * idProviderPtr, const void * authenticationPtr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OPEN_API_C_INTERFACE_H
