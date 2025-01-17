cmake_minimum_required(VERSION 1.6.3)

project(userSetting)

# ---------- Adding required definition flags ---------------------------------
if("$ENV{XCAM_MODEL}" STREQUAL "XHB1")
    add_definitions(-DXHB1)
    set(LIBSTDCXXFS_PATH "${STAGING_DIR_TARGET}/sdk/toolchain/cortex-a53-2022.08-gcc12.1-linux5.15/aarch64-linux-gnu/libc/usr/lib")
elseif("$ENV{XCAM_MODEL}" STREQUAL "XHC3")
    add_definitions(-DXHC3)
    set(LIBSTDCXXFS_PATH "${STAGING_DIR_TARGET}/sdk/toolchain/linaro-armv7ahf-2019.02-gcc7.4/arm-linux-gnueabihf/libc/usr/lib")
else()
    add_definitions(-DXCAM2)
    set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/toolchain/linaro-armv7ahf-2015.11-gcc5.2/arm-linux-gnueabihf/libc/usr/lib")
endif()

# ---------- Setting CXX compiler standard -----------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ---------- Adding source files ---------------------------------------------
include_directories(./include)

set(USER_SETTINGS_SRC src/UserSettingsParser.cpp)
set(USER_SETTINGS_WRAPPER_SRC src/UserSettingsParserWrapper.cpp)

# ---------- Adding filesystem lib path --------------------------------------
link_directories(${LIBSTDCXXFS_PATH})

# ---------- Build required shared lib ---------------------------------------
add_library(userSetting SHARED
    ${USER_SETTINGS_SRC}
    ${USER_SETTINGS_WRAPPER_SRC}
)

# ---------- Linking filesystem library --------------------------------------
target_link_libraries(userSetting stdc++fs)
