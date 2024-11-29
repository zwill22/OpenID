#include "catch.hpp"
#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/ListUserPoolsRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>

TEST_CASE("Test AWS-SDK-CPP include") {
    REQUIRE(true);
}
