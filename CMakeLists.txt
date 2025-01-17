cmake_minimum_required(VERSION 1.6.3)

project(userSetting)

# ---------- Setting CXX compiler standard -----------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ---------- Adding source files ---------------------------------------------
include_directories(./include)

set(USER_SETTINGS_SRC src/UserSettingsParser.cpp)
set(USER_SETTINGS_WRAPPER_SRC src/UserSettingsParserWrapper.cpp)

# ---------- Build required shared lib ---------------------------------------
add_library(userSetting SHARED
    ${USER_SETTINGS_SRC}
    ${USER_SETTINGS_WRAPPER_SRC}
)

# ---------- Linking filesystem library --------------------------------------
target_link_libraries(userSetting)
