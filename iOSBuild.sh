#!/bin/bash

scriptPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
echo "Script Path: ${scriptPath}"

cd ${scriptPath}
libraryString=""

builds=( iphoneos iphonesimulator macOS )
libraries=( libOpenID libOpenIDC )
for build in ${builds[@]}; do

	echo "Building for ${build}..."
	cmake --preset ${build}Build
	cmake --build --preset ${build}Build

	for library in ${libraries[@]}; do
		if [ "${build}" == "macOS" ]; then
			releaseDir="Release"
		else
			releaseDir="Release-${build}"
		fi
		if [ ! -e "out/build/${build}Build/${releaseDir}/${library}.a" ]; then 
    			echo "Library ${library}.a not found"
    			exit 1;
		fi

		echo "Library saved to: out/${build}Build/${releaseDir}/${library}.a"
	done

	libraryString="${libraryString} -library out/build/${build}Build/${releaseDir}/\${library}.a"
done

for library in libOpenID libOpenIDC; do
	libString=$(eval echo ${libraryString})
    	xcodebuild -create-xcframework ${libString} -output out/build/${library}.xcframework
done
