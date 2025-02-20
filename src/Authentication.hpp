#ifndef OPEN_ID_AUTHENTICATION_HPP
#define OPEN_ID_AUTHENTICATION_HPP

#include <memory>
#include <map>
#include <string>

namespace OpenID {

/// @brief Structure for storing results of authentication
struct Authentication {
    /// @brief Access Token for API
    std::string accessToken;

    /// @brief Time (in seconds) which authentication is valid for
    size_t expiryTime;

    /// @brief Identity token for API
    std::string idToken;

    /// @brief Refresh token, for refreshing authentication with API
    std::string refreshToken;

    /// @brief Type of the access token
    std::string tokenType;
};

} // namespace OpenID

#endif // OPEN_ID_AUTHENTICATION_HPP
