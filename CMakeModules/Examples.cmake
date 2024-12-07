if (NOT DEFINED BUILD_EXAMPLES)
    set(BUILD_EXAMPLES OFF)
    message(STATUS "Example executables available to build, to enable set BUILD_EXAMPLES=ON")
endif()


if (BUILD_EXAMPLES)
    message(STATUS "BUILD_EXAMPLES=ON, example executables will be built")
else()
    message(STATUS "BUILD_EXAMPLES=OFF, example executables will not be built")
endif()
