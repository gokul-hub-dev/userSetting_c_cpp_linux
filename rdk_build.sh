#!/bin/bash

##########################################################################
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2019 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################


#######################################
#
# Build Framework standard script for
#
# rdklogger component

# use -e to fail on any shell issue
# -e is the requirement from Build Framework
set -e
# Set environment variables
export RDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH:-$(readlink -m ..)}
export RDK_TOOLCHAIN_PATH=$RDK_PROJECT_ROOT_PATH/sdk/toolchain/arm-linux-gnueabihf
export RDK_SCRIPTS_PATH=${RDK_SCRIPTS_PATH:-$(readlink -m $0 | xargs dirname)}
export RDK_SOURCE_PATH=${RDK_SOURCE_PATH:-$(readlink -m .)}
export RDK_TARGET_PATH=${RDK_TARGET_PATH:-$RDK_SOURCE_PATH}
export RDK_COMPONENT_NAME=${RDK_COMPONENT_NAME:-$(basename $RDK_SOURCE_PATH)}
export STRIP=${RDK_TOOLCHAIN_PATH}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-strip
export DCA_PATH=$RDK_SOURCE_PATH
export FSROOT=$RDK_PROJECT_ROOT_PATH/sdk/fsroot/ramdisk

# Print environment variables to confirm they are set
echo "RDK_SOURCE_PATH: $RDK_SOURCE_PATH"
echo "RDK_TARGET_PATH: $RDK_TARGET_PATH"
echo "RDK_COMPONENT_NAME: $RDK_COMPONENT_NAME"
echo "RDK_DIR: $RDK_DIR"

# parse arguments
INITIAL_ARGS=$@

function usage()
{
    set +x
    echo "Usage: `basename $0` [-h|--help] [-v|--verbose] [action]"
    echo "    -h    --help                  : this help"
    echo "    -v    --verbose               : verbose output"
    echo "    -p    --platform  =PLATFORM   : specify platform for rdklogger"
    echo
    echo "Supported actions:"
    echo "      configure, clean, build (DEFAULT), rebuild, install"
}

ARGS=$@


# component-specific vars
export FSROOT=${RDK_FSROOT_PATH}

# functional modules

function configure()
{
    echo "Start configure"

    cd ${RDK_SOURCE_PATH}
    mkdir -p build
    cd build
    cmake -DCMAKE_VERBOSE_MAKEFILE=ON .. \
      -DRDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH} \
      -DINCLUDE_DIR_PATH=${FSROOT}/usr/include \
      -DLIB_PATH=${FSROOT}/usr/lib \
      -DCMAKE_C_COMPILER=${RDK_TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-gcc \
      -DCMAKE_CXX_COMPILER=${RDK_TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-g++
}

function clean()
{
    echo "Start clean"

    cd ${RDK_SOURCE_PATH}
    if [ -d build ]; then
        cd build
        make clean
    fi
}

function install()
{
    echo "Installing the userSetting related binaries/libraries to root file system"
    cd ${RDK_SOURCE_PATH}
    cp -rvf ./build/libuserSetting.so ${FSROOT}/usr/lib/
    cp -rvf ./include/*.h ${FSROOT}/usr/include
}

function build()
{
   cd ${RDK_SOURCE_PATH}/build/
   make
   install
}

function rebuild()
{
    echo "Start rebuild"

    clean
    configure
    build
}
# run the logic

#these args are what left untouched after parse_args
HIT=false

for i in "$ARGS"; do
    case $i in
        configure)  HIT=true; configure ;;
        clean)      HIT=true; clean ;;
        build)      HIT=true; build ;;
        rebuild)    HIT=true; rebuild ;;
        install)    HIT=true; install ;;
        *)
            #skip unknown
        ;;
    esac
done

# if not HIT do build by default
if ! $HIT; then
  clean
  configure
  build
fi
