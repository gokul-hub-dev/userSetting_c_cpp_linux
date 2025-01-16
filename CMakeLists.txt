cmake_minimum_required(VERSION 1.6.3)

PROJECT(userSetting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

IF("$ENV{XCAM_MODEL}" STREQUAL "XHB1" OR "$ENV{XCAM_MODEL}" STREQUAL "XHC3")
  set(LIBSTDCXXFS_PATH "${RDK_PROJECT_ROOT_PATH}sdk/toolchain/cortex-a53-2022.08-gcc12.1-linux5.15/aarch64-linux-gnu/libc/usr/lib")
  link_directories(${LIBSTDCXXFS_PATH})
  target_link_libraries(userSetting stdc++fs)
ENDIF()

# ---------- Adding source files ------------------------------------------------
INCLUDE_DIRECTORIES(./include)

set(USER_SETTINGS_SRC src/UserSettingsParser.cpp)
set(USER_SETTINGS_WRAPPER_SRC src/UserSettingsParserWrapper.cpp)

# ---------- built required shared lib ----------------------------------------
add_library(userSetting SHARED
  ${USER_SETTINGS_SRC}
  ${USER_SETTINGS_WRAPPER_SRC}
)
