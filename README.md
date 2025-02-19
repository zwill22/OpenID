# OpenID

OpenID is an API client using the [AWS SDK for C++](https://aws.amazon.com/sdk-for-cpp/)
for user sign-up, verification and authentication. Designed to authorise users
for the [BusTracker App](https://github.com/zwill22/BusTracker.git).

By default, the library provides a C++ header file for use in other C++ code. A
C header file is also included for use in non-C++ projects.

## Dependencies

- [AWS SDK for C++](https://aws.amazon.com/sdk-for-cpp/)
- [Catch2](https://github.com/catchorg/Catch2)

# Building

The C++ source files may be built (in-source) using
```
cmake .
```
This default build exposes the C++ header and builds the test files which require [Catch2](https://github.com/catchorg/Catch2).
The [AWS SDK for C++](https://aws.amazon.com/sdk-for-cpp/) must include the "cognito-idp" module, this may be built as follows:
```
git clone https://github.com/aws/aws-sdk-cpp
cd aws-sdk-cpp
git submodule update --init --recursive
cmake . -DBUILD_ONLY="cognito-idp"
cmake --build . --config=Release
cmake --build . --target install
```
When building OpenAPI, specifiying
```
cmake . -DUSE_CATCH=OFF
```
may be used to avoid the Catch2 dependency but will disable all test cases.
If built, test cases may be run using
```
ctest --output-on-failure
```
To enable the OpenAPI C interface, use:
```
cmake . -DC_INTERFACE=ON
```
Some C++ executables are included in the "examples" directory, these are not built by default but setting
```
cmake -DBUILD_EXAMPLES=ON
```
will enable them.
