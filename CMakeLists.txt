cmake_minimum_required(VERSION 1.6.3)

PROJECT(userSetting)


IF("$ENV{XCAM_MODEL}" STREQUAL "XHB1" OR "$ENV{XCAM_MODEL}" STREQUAL "XHC3")
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/toolchain/cortex-a53-2022.08-gcc12.1-linux5.15/aarch64-linux-gnu/libc/usr/lib")
ELSE()
  set(SHADOW_ROOT_LIB_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/fsroot/src/vendor/img/fs/shadow_root/usr/lib")
  set(AMBA_DIR_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/fsroot/src/amba")
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}/sdk/toolchain/linaro-armv7ahf-2015.11-gcc5.2/arm-linux-gnueabihf/libc/usr/lib")
ENDIF()

# ---------- Adding required definition flags ---------------------------------
IF("$ENV{XCAM_MODEL}" STREQUAL "XHB1")
  ADD_DEFINITIONS(-DXHB1)
ENDIF()
IF("$ENV{XCAM_MODEL}" STREQUAL "XHC3")
  ADD_DEFINITIONS(-DXHC3)
ENDIF()
IF(NOT("$ENV{XCAM_MODEL}" STREQUAL "XHB1" OR "$ENV{XCAM_MODEL}" STREQUAL "XHC3"))
  ADD_DEFINITIONS(-DXCAM2)
ENDIF()

# ---------- Setting CXX compiler standard -------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

# ---------- Adding library & executables to be built ----------------------------------------
target_link_libraries(userSetting stdc++fs)
