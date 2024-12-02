target_include_directories(OpenBusAPIClient PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_sources(
    OpenBusAPIClient PRIVATE
    api_client.cpp
    authentication.cpp
    identity_provider.cpp
)
