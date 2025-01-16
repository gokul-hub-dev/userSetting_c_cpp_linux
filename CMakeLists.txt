cmake_minimum_required(VERSION 1.6.3)

PROJECT(userSetting)

# ---------- Setting CXX compiler standard -------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ---------- Adding required definition flags ---------------------------------
IF("$ENV{XCAM_MODEL}" STREQUAL "XHB1")
  ADD_DEFINITIONS(-DXHB1)
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}sdk/toolchain/linaro-armv7ahf-2019.02-gcc7.4/arm-linux-gnueabihf/libc/usr/lib")
ENDIF()
IF("$ENV{XCAM_MODEL}" STREQUAL "XHC3")
  ADD_DEFINITIONS(-DXHC3)
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}sdk/toolchain/cortex-a53-2022.08-gcc12.1-linux5.15/aarch64-linux-gnu/libc/usr/lib")
ENDIF()
IF(NOT("$ENV{XCAM_MODEL}" STREQUAL "XHB1" OR "$ENV{XCAM_MODEL}" STREQUAL "XHC3"))
  ADD_DEFINITIONS(-DXCAM2)
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/toolchain/linaro-armv7ahf-2015.11-gcc5.2/arm-linux-gnueabihf/libc/usr/lib")
ENDIF()

# ---------- Adding filesystem lib path ---------------------------------------------------------
link_directories(${LIBSTDCXXFS_PATH})

# ---------- Adding source files ------------------------------------------------
INCLUDE_DIRECTORIES(./include)

set(USER_SETTINGS_SRC src/UserSettingsParser.cpp)
set(USER_SETTINGS_WRAPPER_SRC src/UserSettingsParserWrapper.cpp)

# ---------- built required shared lib ----------------------------------------
add_library(userSetting SHARED
  ${USER_SETTINGS_SRC}
  ${USER_SETTINGS_WRAPPER_SRC}
)

target_link_libraries(userSetting stdc++fs)
