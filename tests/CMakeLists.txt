add_library(catch SHARED catch.hpp)
target_link_libraries(catch Catch2::Catch2WithMain)
target_include_directories(catch
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
)

add_executable(test-aws-sdk test_aws_sdk.cpp)
target_link_libraries(test-aws-sdk catch ${AWSSDK_LINK_LIBRARIES})
catch_discover_tests(test-aws-sdk)

add_executable(test-include test_include.cpp)
target_link_libraries(test-include catch OpenBusAPIClient)
catch_discover_tests(test-include)
