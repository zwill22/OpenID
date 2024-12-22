# Required for Github runner
cmake_minimum_required(VERSION 3.22)
project(OpenID VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # For compatibility with AWS-SDK
set(SERVICE_COMPONENTS cognito-idp)

message(STATUS "CMAKE VERSION: ${CMAKE_VERSION}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(AWSSDK REQUIRED COMPONENTS ${SERVICE_COMPONENTS})

add_library(OpenID)
target_link_libraries(OpenID PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_include_directories(OpenID PUBLIC ${CMAKE_SOURCE_DIR}/include)

include(CLibrarySetup)
if (C_INTERFACE)
    add_library(OpenIDC)
    target_link_libraries(OpenIDC PRIVATE OpenID)
    target_include_directories(OpenIDC PUBLIC ${CMAKE_SOURCE_DIR}/include)
endif()

add_subdirectory(src)

include(CatchSetup)
if(USE_CATCH)
    if(FOUND_CATCH)
        add_subdirectory(tests)
    endif()
endif()

include(Examples)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
