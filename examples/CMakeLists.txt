add_executable(SignUpExample SignUp.cpp)
target_link_libraries(SignUpExample OpenID)

add_executable(AuthenticationExample Authenticate.cpp)
target_link_libraries(AuthenticationExample OpenID)

add_executable(DeleteUserExample DeleteUser.cpp)
target_link_libraries(DeleteUserExample OpenID)

if (C_INTERFACE)
    add_executable(CInterfaceExample CInterface.cpp)
    target_link_libraries(CInterfaceExample OpenIDC)
endif()
