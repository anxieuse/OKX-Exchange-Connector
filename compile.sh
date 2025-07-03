#!/bin/bash

# Compile the project
cd /home/leo/dev/work/flux/OKX-Exchange-Connector/build
cmake .. -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .