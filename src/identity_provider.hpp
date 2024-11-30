#ifndef OPEN_BUS_COGNITO_IDENTITY_HPP
#define OPEN_BUS_COGNITO_IDENTITY_HPP

#include <string>

namespace OpenBus {

class IDProvider {
    public:
    IDProvider(
        const std::string & userName,
        const std::string & userPassword,
        const std::string & userEmail
    );

    ~IDProvider();

    void signUpUser() const;
    void verifyUser() const;

    private:
    std::string userID;
    std::string password;
    std::string emailAddress;

    struct Options;
    std::unique_ptr<Options> options;

    struct Client;
    std::unique_ptr<Client> client;
};
    

} // namespace OpenBus

#endif // OPEN_BUS_COGNITO_IDENTITY_HPP
