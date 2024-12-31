cmake_minimum_required(VERSION 1.6.3)

PROJECT(userSetting)

# ---------- Adding source files ------------------------------------------------
INCLUDE_DIRECTORIES(./include)

set(USER_SETTINGS_SRC src/UserSettingsParser.cpp)
set(USER_SETTINGS_WRAPPER_SRC src/UserSettingsParserWrapper.cpp)

# ---------- Adding library & executables to be built ----------------------------------------
add_library(userSetting SHARED
  ${USER_SETTINGS_SRC}
  ${USER_SETTINGS_WRAPPER_SRC}
)
