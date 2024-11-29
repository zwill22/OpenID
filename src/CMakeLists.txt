target_include_directories(OpenBusAPIClient PUBLIC ${CMAKE_BINARY_DIR}/src)

target_sources(OpenBusAPIClient PRIVATE sign_up.cpp)
