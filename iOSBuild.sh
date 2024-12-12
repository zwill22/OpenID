#!/bin/bash

scriptPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
echo "Script Path: ${scriptPath}"

cd ${scriptPath}

for build in iOS iOSSimulator; do

echo "Building for ${build}..."
cmake --preset ${build}Build
cmake --build --preset ${build}Build

for library in libOpenID libOpenIDC; do
if [ ! -e "out/build/${build}Build/${library}.a" ]; then 
    echo "Library ${library}.a not found"
    exit 1;
fi
done

done

for library in libOpenID libOpenIDC; do
    xcodebuild -create-xcframework -library out/build/iOSBuild/${library}.a -library out/build/iOSSimulatorBuild/${library}.a -output out/build/${library}.xcframework
done
