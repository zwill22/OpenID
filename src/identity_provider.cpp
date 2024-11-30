#include "identity_provider.hpp"

#include "sign_up.hpp"

namespace OpenBus {

IDProvider::IDProvider(
    const std::string & userName,
    const std::string & userPassword,
    const std::string & userEmail
) : userID(userName),
    password(userPassword),
    emailAddress(userEmail)
{}

IDProvider::~IDProvider() {}

void IDProvider::signUpUser() const {
    OpenBus::signUpUser(userID, password, emailAddress);
}

} // namespace OpenBus
