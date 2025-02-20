#ifndef OPEN_ID_API_CLIENT_HPP
#define OPEN_ID_API_CLIENT_HPP

#include <string>
#include <memory>
 
namespace OpenID {

/// @brief Class for managing the AWS APIClient
///
/// This class must be initialised before any ID provider.
class APIClient {
    public:
    /// @brief Initialise an `APIClient`
    APIClient();

    /// @brief Deinitialise an `APIClient
    ~APIClient();

    private:
    struct Options;
    std::unique_ptr<Options> options;
};
    

} // namespace OpenID

#endif // OPEN_ID_API_CLIENT_HPP
