#ifndef OPEN_API_IDENTITY_PROVIDER_HPP
#define OPEN_API_IDENTITY_PROVIDER_HPP

#include <string>
#include <memory>

#include "authentication.hpp"

namespace OpenAPI {

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
    

} // namespace OpenAPI

#endif // OPEN_API_IDENTITY_PROVIDER_HPP
