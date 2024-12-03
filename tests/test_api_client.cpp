#include "catch.hpp"

#include "api_client.hpp"

TEST_CASE("Test Open API Client") {
    REQUIRE_NOTHROW(OpenAPI::APIClient());
}
