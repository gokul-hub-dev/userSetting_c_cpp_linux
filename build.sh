#!/bin/bash
rm -rf build
rm -rf main
mkdir build
cd build
cmake ..
make
export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH
