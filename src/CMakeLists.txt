target_include_directories(OpenAPIClient PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_sources(
    OpenAPIClient PRIVATE
    api_client.cpp
    identity_provider.cpp
)

if (C_INTERFACE)
    target_sources(
        OpenAPICClient PRIVATE
        interface.cpp
    )
endif()
