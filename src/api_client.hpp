#ifndef OPEN_API_CLIENT_HPP
#define OPEN_API_CLIENT_HPP

#include <string>
#include <memory>

namespace OpenAPI {

class APIClient {
    public:
    APIClient();
    ~APIClient();

    private:
    struct Options;
    std::unique_ptr<Options> options;
};
    

} // namespace OpenAPI

#endif // OPEN_API_CLIENT_HPP
