#ifndef OPEN_ID_H
#define OPEN_ID_H

#include <stdbool.h>
#include <stddef.h>

// C-header for OpenID library

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


void* initialiseOpenIDClient();
size_t openIDClientSize();

void* initialiseOpenIDProvider(
    const char * userID,
    const char * password,
    const char * emailAddress,
    const char * clientRegion,
    const char * clientID
);
size_t idProviderSize();

bool signUpUser(const void * idProviderPtr);
bool verifyUser(const void * idProviderPtr, const char * confirmationCode);
bool resendCode(const void * idProviderPtr);

void* authenticate(const void * idProviderPtr);
size_t authenticationSize();

char* getAccessToken(void * authenticationPtr);
int getExpiryTime(void * authenticationPtr);
char* getIDToken(void * authenticationPtr);
char* getRefreshToken(void * authenticationPtr);
char* getTokenType(void * authenticationPtr);

bool deleteUser(const void * idProviderPtr, const void * authenticationPtr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OPEN_ID_H
