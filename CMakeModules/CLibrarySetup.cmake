if (NOT DEFINED C_INTERFACE)
    set(C_INTERFACE OFF)
endif()

if (C_INTERFACE)
    message(STATUS "C_INTERFACE=ON: C interface functions will be built")
else()
    message(STATUS "C_WRAPPER=OFF: C interface functions will not be built")
endif()