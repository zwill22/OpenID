#include "Catch.hpp"

#include "OpenID.h"
#include "OpenID.hpp"

#include <iostream>

using namespace OpenID;

void* getAuthenticationCPtr(const Authentication & authentication) {
    return (void *) &authentication;
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

TEST_CASE("Test get Authentication functions") {
    Authentication authentication; 
    authentication.accessToken = "wertyuiufghjgftgfghyhdgwsyuhgdhs";
    authentication.expiryTime = 3600;
    authentication.idToken = "dertyujhbvftyujhgftrdcvbnbdsnakjhgsn";
    authentication.refreshToken = "vhjhgyhghjefgehweuwhdjhgdhsjudhghsjbdh";
    authentication.tokenType = "Bearer";

    auto authenticationCPtr  = getAuthenticationCPtr(authentication);

    const std::string accessToken = getAccessToken(authenticationCPtr);
    const int expiryTime = getExpiryTime(authenticationCPtr);
    const std::string idToken = getIDToken(authenticationCPtr);
    const std::string refreshToken = getRefreshToken(authenticationCPtr);
    const std::string tokenType = getTokenType(authenticationCPtr);

    printAuthentication(accessToken, expiryTime, idToken, refreshToken, tokenType);

    REQUIRE(accessToken == authentication.accessToken);
    REQUIRE(expiryTime == authentication.expiryTime);
    REQUIRE(idToken == authentication.idToken);
    REQUIRE(refreshToken == authentication.refreshToken);
    REQUIRE(tokenType == authentication.tokenType);
}
