if (NOT DEFINED IOS_BUILD)
    set(IOS_BUILD OFF)
endif()

if (IOS_BUILD)
    message(STATUS "IOS_BUILD=ON, static iOS library will be built")
else()
    message(STATUS "IOS_BUILD=OFF, enable to built static iOS library")
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    iOSToolChain
    GIT_REPOSITORY https://github.com/leetal/ios-cmake.git
    )
FetchContent_MakeAvailable(iOSToolChain)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/_deps/iostoolchain-src/ios.toolchain.cmake)
if (EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "Toolchain file not found")
endif()
set(PLATFORM OS64)
