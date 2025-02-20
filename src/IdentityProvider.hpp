#ifndef OPEN_ID_IDENTITY_PROVIDER_HPP
#define OPEN_ID_IDENTITY_PROVIDER_HPP

#include <string>
#include <memory>

#include "Authentication.hpp"

namespace OpenID {

/// @brief Structure holding all settings for the ::IDProvider class
struct IDSettings {
    /// User credentials
    std::string userID; 
    std::string password;
    std::string emailAddress;

    /// Client credentials
    std::string clientRegion;
    std::string clientID;
};

/// @brief Class which manages the identity of the user and interacts with the client.
class IDProvider {
public:
    /// @brief Initialise the IDProvider with settings `idSettings`
    ///
    /// @param idSettings Structure of type ::IDSettings
    IDProvider(const IDSettings &idSettings);

    /// @brief Deinitialise an IDProvider class
    ~IDProvider();

    /// @brief Signs up a new user to the client
    ///
    /// Signs up user with the stored credentials to the corresponding client
    void signUpUser() const;

    /// @brief Verifies user to the client using a confirmation code
    ///
    /// @param confirmationCode Confirmation code (should be sent to email provided)
    void verifyUser(const std::string & confirmationCode) const;

    /// @brief Request the client send a new confirmation code to the `emailAddress`
    void resendCode() const;

    /// @brief Request authentication credentials for the user from the client
    ///
    /// @return Authentication credentials
    Authentication passwordAuthenticate() const;

    /// @brief Request user be deleted from client
    ///
    /// @param authentication Authentication credentials (required for deletion)
    void deleteUser(const Authentication & authentication) const;

private:
    IDSettings settings;

    struct IDProviderClient;
    std::unique_ptr<IDProviderClient> idProviderClient;
};
    

} // namespace OpenID

#endif // OPEN_ID_IDENTITY_PROVIDER_HPP
