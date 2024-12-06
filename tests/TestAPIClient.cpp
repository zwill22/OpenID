#include "Catch.hpp"

#include "OpenID.hpp"

TEST_CASE("Test OpenID API Client") {
    REQUIRE_NOTHROW(OpenID::APIClient());
}
