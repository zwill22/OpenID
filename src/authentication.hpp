#ifndef OPEN_BUS_AUTHENTICATION_HPP
#define OPEN_BUS_AUTHENTICATION_HPP

#include <memory>
#include <map>
#include <string>

namespace OpenBus {

typedef std::map<std::string, std::string> AuthenticationResult;

template <typename ResultType>
AuthenticationResult getResults(const ResultType & result) {
    AuthenticationResult authResults = {};

    // Access token
    if (!result.AccessTokenHasBeenSet()) {
        throw std::runtime_error("AccessToken not set");
    }
    authResults["AccessToken"] = result.GetAccessToken();

    // Expiry time
    if (!result.ExpiresInHasBeenSet()) {
        throw std::runtime_error("ExpiresIn time not set");
    }
    authResults["RefreshToken"] = result.GetExpiresIn();

    // ID token
    if (!result.IdTokenHasBeenSet()) {
        throw std::runtime_error("IDToken not set");
    }
    authResults["IDToken"] = result.GetIdToken();
    
    // Refresh token
    if (!result.RefreshTokenHasBeenSet()) {
        throw std::runtime_error("RefreshToken not set");
    }
    authResults["RefreshToken"] = result.GetRefreshToken();

    // Token type
    if (!result.TokenTypeHasBeenSet()) {
        throw std::runtime_error("TokenType not set");
    }
    authResults["TokenType"] = result.GetTokenType();

    return authResults;
}

class Authentication {
public:    
    Authentication(AuthenticationResult result);
    ~Authentication();

private:
    AuthenticationResult authenticationResult;
};

}

#endif // OPEN_BUS_AUTHENTICATION_HPP
