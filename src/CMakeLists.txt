target_include_directories(OpenBusAPIClient PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_sources(
    OpenBusAPIClient PRIVATE
    identity_provider.cpp
    sign_up.cpp
)
