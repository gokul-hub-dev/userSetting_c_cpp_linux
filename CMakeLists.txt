cmake_minimum_required(VERSION 1.6.3)

PROJECT(userSetting)

IF(NOT("$ENV{XCAM_MODEL}" STREQUAL "XHB1" OR "$ENV{XCAM_MODEL}" STREQUAL "XHC3"))
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
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
