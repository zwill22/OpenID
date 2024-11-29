# Required for Github runner
cmake_minimum_required(VERSION 3.22)
message(STATUS "CMAKE VERSION: ${CMAKE_VERSION}")

project(OpenBusAPIClient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SERVICE_COMPONENTS cognito-idp)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

find_package(AWSSDK REQUIRED COMPONENTS ${SERVICE_COMPONENTS})

add_library(OpenBusAPIClient SHARED)

target_link_libraries(OpenBusAPIClient ${AWSSDK_LINK_LIBRARIES})
target_include_directories(OpenBusAPIClient INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

if (NOT DEFINED USE_CATCH)
    set(USE_CATCH ON)
    message(STATUS "Setting up Catch2 for unit testing, to disable set USE_CATCH=OFF")
endif ()

if (USE_CATCH)
    find_package(Catch2 3)
    if (${Catch2_DIR} MATCHES "Catch2_DIR_NOTFOUND")
        message(STATUS "Catch2 not found -- Cannot build tests")
        set(FOUND_CATCH FALSE)
    else ()
        message(STATUS "Catch2 found")
        message(STATUS "Catch2_DIR: ${Catch2_DIR}")
        set(FOUND_CATCH TRUE)
    endif ()
endif ()

if (USE_CATCH)
    if (FOUND_CATCH)
        include(CTest)
        include(Catch)

        enable_testing()

        add_subdirectory(tests)
    endif ()
endif ()
