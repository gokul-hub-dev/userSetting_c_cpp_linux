#include "UserSettingsParser.h"
#include <cstring> // For strncpy

extern "C" {

// Function to create the settings file if it doesn't exist
void create_file_if_not_exists(const char* filename) {
    try {
        UserSettingsParser::getInstance().createFileIfNotExists(filename);
    } catch (const std::exception& e) {
        // Handle exception (log or return error code)
    }
}

// Function to load settings from a file
void load_settings(const char* filename) {
    try {
        UserSettingsParser::getInstance().loadSettings(filename);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to get a value as a string
const char* get_value(const char* key) {
    try {
        static std::string value = UserSettingsParser::getInstance().getValue(key);
        return value.c_str();
    } catch (const std::exception& e) {
        return nullptr; // Indicate error
    }
}

// Function to get a value as an integer
int get_value_as_int(const char* key) {
    try {
        return UserSettingsParser::getInstance().getValueAs<int>(key);
    } catch (const std::exception& e) {
        return -1; // Indicate error
    }
}

// Function to get a value as a double
double get_value_as_double(const char* key) {
    try {
        return UserSettingsParser::getInstance().getValueAs<double>(key);
    } catch (const std::exception& e) {
        return -1.0; // Indicate error
    }
}

// Function to get a value as a boolean
int get_value_as_bool(const char* key) {
    try {
        return UserSettingsParser::getInstance().getValueAs<bool>(key) ? 1 : 0;
    } catch (const std::exception& e) {
        return -1; // Indicate error
    }
}

// Function to set a string value
void set_value(const char* key, const char* value) {
    try {
        UserSettingsParser::getInstance().setValue(key, value);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to set an integer value
void set_value_as_int(const char* key, int value) {
    try {
        UserSettingsParser::getInstance().setValueAs<int>(key, value);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to set a double value
void set_value_as_double(const char* key, double value) {
    try {
        UserSettingsParser::getInstance().setValueAs<double>(key, value);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to set a boolean value
void set_value_as_bool(const char* key, int value) {
    try {
        UserSettingsParser::getInstance().setValueAs<bool>(key, value != 0);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to save settings
void save_settings() {
    try {
        UserSettingsParser::getInstance().saveSettings();
    } catch (const std::exception& e) {
        // Handle exception
    }
}

// Function to save settings to a specific file
void save_settings_as(const char* filename) {
    try {
        UserSettingsParser::getInstance().saveSettingsAs(filename);
    } catch (const std::exception& e) {
        // Handle exception
    }
}

}
