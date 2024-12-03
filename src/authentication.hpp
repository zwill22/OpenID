#ifndef OPEN_API_AUTHENTICATION_HPP
#define OPEN_API_AUTHENTICATION_HPP

#include <memory>
#include <map>
#include <string>

namespace OpenAPI {

struct Authentication {
    std::string accessToken;
    size_t expiryTime;
    std::string idToken;
    std::string refreshToken;
    std::string tokenType;
};

template <typename AuthenticationResult>
Authentication authenticateResults(const AuthenticationResult & result) {
    Authentication authResults;

    // Access token
    if (!result.AccessTokenHasBeenSet()) {
        throw std::runtime_error("AccessToken not set");
    }
    authResults.accessToken = result.GetAccessToken();

    // Expiry time
    if (!result.ExpiresInHasBeenSet()) {
        throw std::runtime_error("ExpiresIn time not set");
    }
    authResults.expiryTime = result.GetExpiresIn();

    // ID token
    if (!result.IdTokenHasBeenSet()) {
        throw std::runtime_error("IDToken not set");
    }
    authResults.idToken = result.GetIdToken();
    
    // Refresh token
    if (!result.RefreshTokenHasBeenSet()) {
        throw std::runtime_error("RefreshToken not set");
    }
    authResults.refreshToken = result.GetRefreshToken();

    // Token type
    if (!result.TokenTypeHasBeenSet()) {
        throw std::runtime_error("TokenType not set");
    }
    authResults.tokenType = result.GetTokenType();

    return authResults;
}

} // namespace OpenAPI

#endif // OPEN_API_AUTHENTICATION_HPP
