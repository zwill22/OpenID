add_executable(SignUpExample signup.cpp)
target_link_libraries(SignUpExample OpenAPIClient)

add_executable(AuthenticationExample authenticate.cpp)
target_link_libraries(AuthenticationExample OpenAPIClient)

add_executable(DeleteUserExample delete_user.cpp)
target_link_libraries(DeleteUserExample OpenAPIClient)

if (C_INTERFACE)
    add_executable(CInterfaceExample c_interface.cpp)
    target_link_libraries(CInterfaceExample OpenAPICClient)
endif()
