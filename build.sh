#!/bin/bash

set -eu

rm -rf build

mkdir build
cd build

cmake --preset $BUILD_CONF ..
cmake --build .
