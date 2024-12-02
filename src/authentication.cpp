#include "authentication.hpp"

#include <aws/cognito-idp/model/RespondToAuthChallengeResult.h>

namespace OpenBus {

Authentication::Authentication(AuthenticationResult result)
{
    authenticationResult = result;
}

Authentication::~Authentication()
{
}

}
