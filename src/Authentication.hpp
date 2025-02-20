#ifndef OPEN_ID_AUTHENTICATION_HPP
#define OPEN_ID_AUTHENTICATION_HPP

#include <memory>
#include <map>
#include <string>

namespace OpenID {

/// @brief Structure for storing results of authentication
struct Authentication {
    std::string accessToken;
    size_t expiryTime;
    std::string idToken;
    std::string refreshToken;
    std::string tokenType;
};

} // namespace OpenID

#endif // OPEN_ID_AUTHENTICATION_HPP
