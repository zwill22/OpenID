#ifndef OPEN_ID_H
#define OPEN_ID_H

#include <stdbool.h>
#include <stddef.h>

// C-header for OpenID library

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief Initialise the `OpenIDClient` interface
///
/// Must be before any other functions
///
/// @param openIDClient Pointer for `OpenIDClient`
///
/// @return Success
bool initialiseOpenIDClient(void* openIDClient);

/// @brief Uninitialise an OpenID client object
///
/// @param openIDClient Pointer to (initialised) OpenIDClient
///
/// @return Success
bool uninitialiseOpenIDClient(void* openIDClient);

/// @brief Determine size of memory required for OpenIDClient object
///
/// @return Required size
size_t openIDClientSize();

/// @brief Initialise an `OpenIDProvider`
///
/// Initialises an `OpenIDProvider` object at pointer `idProvider`.
///
/// @param idProvider Pointer for `OpenIDProvider` object 
/// @param userID New or existing user ID for the client API
/// @param password Password for the user
/// @param emailAddress User e-mail address
/// @param clientRegion AWS Client region
/// @param clientID AWS Client ID
///
/// @return Success
bool initialiseOpenIDProvider(
    void * idProvider,
    const char * userID,
    const char * password,
    const char * emailAddress,
    const char * clientRegion,
    const char * clientID
);

/// @brief Uninitialise an `OpenIDProvider` object
///
/// @param idProvider Pointer to existing `OpenIDProvider`
///
/// @return Success
bool uninitialiseOpenIDProvider(void* idProvider);

/// @brief Obtain amount of memory required for an `OpenIDProvider` object
///
/// @return Amount of memory required
size_t idProviderSize();

/// @brief Sign up user to client
///
/// Sign up a new user with `userID`, `password`, and `emailAddress` to the
/// client identified by `clientRegion` and `clientID`.
///
/// @param idProviderPtr Pointer to `OpenIDProvider`
///
/// @return Success
bool signUpUser(const void * idProviderPtr);

/// @brief Verify an unverified user using confirmation code.
///
/// A new user must be verified using a code e-mailed to address `emailAddress`.
/// If the verification code is valid for used with id `userID` then the function
/// returns `true`.
///
/// @param idProviderPtr Pointer to `OpenIDProvider`
/// @param confirmationCode Confirmation code
///
/// @return Success
bool verifyUser(const void * idProviderPtr, const char * confirmationCode);

/// @brief Request a new code be sent to `emailAddress`
///
/// Request a new code for user `userID` be sent to their `emailAddress`. If
/// the user is signed up with the email provided then a code should be resent.
///
/// @param idProviderPtr Pointer to `OpenIDProvider`
///
/// @return Successfully resent code
bool resendCode(const void * idProviderPtr);

/// @brief Request authentication for the user from the client
///
/// Requests authentication for the user with credentials `userID`, `password`, and
/// `emailAddress` from the client `clientID` in `clientRegion`. Successful 
/// authentication populates the `authentication` struct with the necessary
/// authentication tokens.
///
/// @param authentication Pointer to struct for holding authentication tokens
/// @param idProviderPtr Pointer to `OpenIDProvider` object
///
/// @return Successful authentication
bool authenticate(void* authentication, void * idProviderPtr);

/// @brief Get the amount of memory required for an `Authentication` struct
///
/// @return Amount of memory for an `Authentication` struct
size_t authenticationSize();

/// @brief Retrieve the access token from the `Authentication` struct
///
/// @param authenticationPtr Pointer to (valid) authentication struct
///
/// @return Access token as a character array
char* getAccessToken(void * authenticationPtr);

/// @brief Retrieve the expiry time (in seconds) from the `Authentication` struct
///
/// @param authenticationPtr Pointer to the `Authentication` object
///
/// @return Return time in seconds that authentication is valid for
int getExpiryTime(void * authenticationPtr);

/// @brief Retrieve the ID token from the `Authentication` struct
///
/// @param authenticationPtr Pointer to the `Authentication` object
///
/// @return ID token as a character array
char* getIDToken(void * authenticationPtr);

/// @brief Retrieve the refresh token from the `Authentication` struct
///
/// @param authenticationPtr Pointer to the `Authentication` object
///
/// @return Refresh token as a character array
char* getRefreshToken(void * authenticationPtr);

/// @brief Retrieve the token type from the `Authentication` struct
///
/// @param authenticationPtr Pointer to the `Authentication` object
///
/// @return Token type as a character array 
char* getTokenType(void * authenticationPtr);

/// @brief Request user deletion from client using valid authentication
///
/// Request that the user with credentials stored in `idProviderPtr` be
/// deleted from the client using the authentication in `authenticationPtr`.
///
/// @param idProviderPtr Pointer to the `OpenIDProvider` object
/// @param authenticationPtr Pointer to the `Authentication` object
///
/// @return Successful deletion
bool deleteUser(const void * idProviderPtr, const void * authenticationPtr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OPEN_ID_H
