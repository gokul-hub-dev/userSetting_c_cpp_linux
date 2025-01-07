#ifndef USER_SETTINGS_PARSER_HPP
#define USER_SETTINGS_PARSER_HPP

#include <string>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>

#define SECURE_MOUNT_FLAG_FILE "/tmp/.SecurePartition"
#define SECURE_USR_CONFIG_FILE_PATH "/opt/SecurePartition/usr_config/"
#define USR_CONFIG_FILE_PATH "/opt/usr_config/"

#define SECURE_WPA_CONFIG_FILE_PATH "/opt/SecurePartition/wifi/"
#define WPA_CONFIG_FILE_PATH "/opt/secure/wifi/"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

/**
 * @class UserSettingsParser
 * @brief Singleton class responsible for loading, retrieving, and saving user settings from a file.
 *
 * The UserSettingsParser class provides an interface to load settings from a file, retrieve values by key,
 * set new values, and save the settings back to a file. This class supports generic type conversion using
 * template functions for retrieving and setting values in different types (e.g., int, double, bool).
 */
class UserSettingsParser {
public:
    static UserSettingsParser& getInstance();
    void createFileIfNotExists(const std::string& filename);
    void loadSettings(const std::string& filename);
    std::string getValue(const std::string& key);
    template<typename T>
    T getValueAs(const std::string& key);
    void setValue(const std::string& key, const std::string& value);
    template<typename T>
    void setValueAs(const std::string& key, const T& value);
    void saveSettings();
    void saveSettingsAs(const std::string& filename);
    const char* getUsrConfigPath(void);
    const char* getWifiConfigPath(void);

private:
    UserSettingsParser() = default;
    ~UserSettingsParser() = default;
    UserSettingsParser(const UserSettingsParser&) = delete;
    UserSettingsParser& operator=(const UserSettingsParser&) = delete;

    std::unordered_map<std::string, std::string> settings_;
    std::mutex mutex_;
    std::string currentFilename_;
};
#endif
