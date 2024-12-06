target_include_directories(OpenID PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_sources(
    OpenID PRIVATE
    APIClient.cpp
    IdentityProvider.cpp
)

if (C_INTERFACE)
    target_sources(
        OpenIDC PRIVATE
        Interface.cpp
    )
endif()
