#ifndef OPEN_BUS_SIGN_UP_HPP
#define OPEN_BUS_SIGN_UP_HPP

#include <string>

namespace OpenBus {

    /// @brief Sign a user up to the Cognito server
    void signUpUser(
        const std::string & userName,
        const std::string & password,
        const std::string & email
    );

} // namespace OpenBus

#endif // OPEN_BUS_SIGN_UP_HPP
