#ifndef OPEN_BUS_COGNITO_IDENTITY_HPP
#define OPEN_BUS_COGNITO_IDENTITY_HPP

#include <string>
#include <memory>

#include "identity.hpp"

namespace OpenBus {

class IDProvider {
public:
    IDProvider(const IDSettings &idSettings);

    ~IDProvider();

    void signUpUser() const;
    void verifyUser(const std::string & confirmationCode) const;
    void resendCode() const;

    void passwordAuth();

private:
    IDSettings settings;

    struct IDProviderClient;
    std::unique_ptr<IDProviderClient> idProviderClient;

    struct AuthenticationResult;
    std::unique_ptr<AuthenticationResult> authenticationResult;
};
    

} // namespace OpenBus

#endif // OPEN_BUS_COGNITO_IDENTITY_HPP
