#ifndef OPEN_ID_API_CLIENT_HPP
#define OPEN_ID_API_CLIENT_HPP

#include <string>
#include <memory>

namespace OpenID {

class APIClient {
    public:
    APIClient();
    ~APIClient();

    private:
    struct Options;
    std::unique_ptr<Options> options;
};
    

} // namespace OpenID

#endif // OPEN_ID_API_CLIENT_HPP
