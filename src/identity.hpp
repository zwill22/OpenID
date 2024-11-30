#ifndef OPEN_BUS_IDENTITY_HPP
#define OPEN_BUS_IDENTITY_HPP

#include <string>

namespace OpenBus {

struct IDSettings {
    std::string userID;
    std::string password;
    std::string emailAddress;

    std::string clientRegion;
    std::string clientID;
};

} // namespace OpenBus 

#endif // OPEN_BUS_IDENTITY_HPP
