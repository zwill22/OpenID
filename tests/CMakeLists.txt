add_library(catch SHARED Catch.hpp)
target_link_libraries(catch Catch2::Catch2WithMain)
target_include_directories(catch
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
)

add_executable(TestInclude TestInclude.cpp)
target_link_libraries(TestInclude catch OpenID)
catch_discover_tests(TestInclude)

add_executable(TestAPIClient TestAPIClient.cpp)
target_link_libraries(TestAPIClient catch OpenID)
catch_discover_tests(TestAPIClient)

add_executable(TestAuthenticationFlow TestAuthentication.cpp)
target_link_libraries(TestAuthenticationFlow catch OpenID)
catch_discover_tests(TestAuthenticationFlow)

if (C_INTERFACE)
add_executable(TestHeaderConsistency TestHeaders.cpp)
target_link_libraries(TestHeaderConsistency catch OpenID OpenIDC)
catch_discover_tests(TestHeaderConsistency)
endif()
