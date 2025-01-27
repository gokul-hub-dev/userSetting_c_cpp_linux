#include "UserSettingsParser.h"
/**
* @brief Retrieves the singleton instance of the UserSettingsParser.
* @return A reference to the singleton UserSettingsParser instance.
*/
UserSettingsParser& UserSettingsParser::getInstance() {
    static UserSettingsParser instance;
    return instance;
}
/**
* @brief Creates the file if it doesn't exist.
* 
* This method checks whether the specified file exists and creates an empty file
* if it is not present.
* 
* @param filename The name of the file to check and possibly create.
* @throws std::runtime_error If the file cannot be created.
*/
void UserSettingsParser::createFileIfNotExists(const std::string& filename) {
    if (!fs::exists(filename)) {
        std::ofstream outfile(filename);
        if (!outfile) {
            throw std::runtime_error("Unable to create settings file: " + filename);
        }
        outfile.close();
    }
}
/**
 * @brief Loads the settings from a specified file.
 * 
 * This function reads key-value pairs from the file, where each line should be formatted as 'key=value'.
 * 
 * @param filename The name of the file to load the settings from.
 * @throws std::runtime_error If the file cannot be opened.
 */
void UserSettingsParser::loadSettings(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Clear the settings map if it is not empty
    if (!settings_.empty()) {
        settings_.clear();
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open settings file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            settings_[key] = value;
        }
    }
    file.close();
    currentFilename_ = filename;
}
/**
 * @brief Retrieves the value associated with the specified key.
 * 
 * @param key The key for which the value should be retrieved.
 * @return The value as a string.
 * @throws std::runtime_error If the key is not found in the settings.
 */
std::string UserSettingsParser::getValue(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = settings_.find(key);
    if (it != settings_.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Setting not found: " + key);
    }
}
/**
 * @brief Retrieves the value associated with the specified key and converts it to the requested type.
 * 
 * Supported types include int, double, and bool (with true/false or 1/0).
 * 
 * @tparam T The type to which the value should be converted.
 * @param key The key for which the value should be retrieved.
 * @return The value converted to the specified type.
 * @throws std::runtime_error If the key is not found or if conversion fails.
 */
template<>
int UserSettingsParser::getValueAs<int>(const std::string& key){
    return std::stoi(getValue(key));
}

template<>
double UserSettingsParser::getValueAs<double>(const std::string& key){
    return std::stod(getValue(key));
}

template<>
bool UserSettingsParser::getValueAs<bool>(const std::string& key){
    std::string value = getValue(key);
    return value == "true" || value == "1";
}
/**
 * @brief Sets a value for the specified key.
 * 
 * @param key The key to set the value for.
 * @param value The value to be associated with the key.
 */
void UserSettingsParser::setValue(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    settings_[key] = value;
}
/**
 * @brief Sets a value for the specified key and converts it from the specified type.
 * 
 * Supported types include int, double, and bool.
 * 
 * @tparam T The type of the value to be set.
 * @param key The key to set the value for.
 * @param value The value to be associated with the key, which will be converted to a string.
 */
template<>
void UserSettingsParser::setValueAs<int>(const std::string& key, const int& value){
    setValue(key, std::to_string(value));
}
template<>
void UserSettingsParser::setValueAs<double>(const std::string& key, const double& value){
    setValue(key, std::to_string(value));
}
template<>
void UserSettingsParser::setValueAs<bool>(const std::string& key, const bool& value){
    setValue(key, value ? "true" : "false");
}
/**
 * @brief Saves the current settings to the last loaded file.
 * 
 * @throws std::runtime_error If no file was previously loaded.
 */
void UserSettingsParser::saveSettings() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (currentFilename_.empty()) {
        throw std::runtime_error("No filename specified for saving settings.");
    }
    saveSettingsAs(currentFilename_);
}
/**
 * @brief Saves the current settings to a specified file.
 * 
 * @param filename The name of the file to save the settings to.
 * @throws std::runtime_error If the file cannot be opened.
 */
void UserSettingsParser::saveSettingsAs(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open settings file: " + filename);
    }

    for (const auto& setting : settings_) {
        file << setting.first << "=" << setting.second << "\n";
    }
    file.close();
    settings_.clear();
}
