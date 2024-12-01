#ifndef OPEN_BUS_IDENTITY_HPP
#define OPEN_BUS_IDENTITY_HPP

#include <string>
#include <memory>

namespace OpenBus {

struct IDSettings {
    std::string userID;
    std::string password;
    std::string emailAddress;

    std::string clientRegion;
    std::string clientID;
};

class Identity {
public:
    Identity(const IDSettings &idSettings);
    ~Identity();

private:
    IDSettings settings;

    struct IDClient;
    std::unique_ptr<IDClient> idClient;
};
    

} // namespace OpenBus 

#endif // OPEN_BUS_IDENTITY_HPP
