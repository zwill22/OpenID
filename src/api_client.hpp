#ifndef OPEN_BUS_API_CLIENT_HPP
#define OPEN_BUS_API_CLIENT_HPP

#include <string>
#include <memory>

namespace OpenBus {

class APIClient {
    public:
    APIClient();
    ~APIClient();

    private:
    struct Options;
    std::unique_ptr<Options> options;
};
    

} // namespace OpenBus

#endif // OPEN_BUS_API_CLIENT_HPP
