#ifndef OPEN_ID_IDENTITY_PROVIDER_HPP
#define OPEN_ID_IDENTITY_PROVIDER_HPP

#include <string>
#include <memory>

#include "Authentication.hpp"

namespace OpenID {

struct IDSettings {
    std::string userID;
    std::string password;
    std::string emailAddress;

    std::string clientRegion;
    std::string clientID;
};

class IDProvider {
public:
    IDProvider(const IDSettings &idSettings);

    ~IDProvider();

    void signUpUser() const;
    void verifyUser(const std::string & confirmationCode) const;
    void resendCode() const;

    Authentication passwordAuthenticate() const;

    void deleteUser(const Authentication & authentication) const;

private:
    IDSettings settings;

    struct IDProviderClient;
    std::unique_ptr<IDProviderClient> idProviderClient;
};
    

} // namespace OpenID

#endif // OPEN_ID_IDENTITY_PROVIDER_HPP
