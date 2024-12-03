add_library(catch SHARED catch.hpp)
target_link_libraries(catch Catch2::Catch2WithMain)
target_include_directories(catch
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
)

add_executable(test-include test_include.cpp)
target_link_libraries(test-include catch OpenBusAPIClient)
catch_discover_tests(test-include)

add_executable(test-api-client test_api_client.cpp)
target_link_libraries(test-api-client catch OpenBusAPIClient)
catch_discover_tests(test-api-client)

add_executable(test-authentication-flow authentication_test.cpp)
target_link_libraries(test-authentication-flow catch OpenBusAPIClient)
catch_discover_tests(test-authentication-flow)
