#ifndef OPEN_ID_ERROR_HPP
#define OPEN_ID_ERROR_HPP

#include <stdexcept>
#include <string>

namespace OpenID {

/// @brief Error thrown by OpenID
struct OpenIDError : public std::runtime_error {

  explicit OpenIDError(const std::string & arg)
    : std::runtime_error("Error: " + arg) {}

  explicit OpenIDError(const char * arg)
    : std::runtime_error("Error: " + std::string(arg)) {}

};

} // namespace OpenID

#endif // OPEN_ID_ERROR_HPP
