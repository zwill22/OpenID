#include "catch.hpp"

#include "api_client.hpp"

TEST_CASE("Test API Client") {
    REQUIRE_NOTHROW(OpenBus::APIClient());
}
