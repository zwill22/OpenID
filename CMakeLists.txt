cmake_minimum_required(VERSION 3.22)
message(STATUS "CMAKE VERSION: ${CMAKE_VERSION}")

project(OpenBusAPIClient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SERVICE_COMPONENTS cognito-idp)

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

find_package(AWSSDK REQUIRED COMPONENTS ${SERVICE_COMPONENTS})

add_executable(OpenBusAPIClient OpenBusAPIClient.cpp)

target_link_libraries(OpenBusAPIClient ${AWSSDK_LINK_LIBRARIES})
