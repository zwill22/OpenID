#include "identity_provider.hpp"

#include "sign_up.hpp"

#include <aws/core/Aws.h>

using namespace Aws::Utils;

namespace OpenBus {

struct IDProvider::Options : public Aws::SDKOptions {};

IDProvider::IDProvider(
    const std::string & userName,
    const std::string & userPassword,
    const std::string & userEmail
) : userID(userName),
    password(userPassword),
    emailAddress(userEmail),
    pOptions(new Options())
{
    Aws::InitAPI(*pOptions);
}

IDProvider::~IDProvider() {
    Aws::ShutdownAPI(*pOptions);
}

void IDProvider::signUpUser() const {
    OpenBus::signUpUser(userID, password, emailAddress);
}

} // namespace OpenBus
