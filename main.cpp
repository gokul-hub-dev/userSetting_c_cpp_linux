#include <stdio.h>
#include <stdlib.h>
#include "UserSettingsParser.h"

#define GETS 1
#define GET 0
#define SET 0 
#define SETS 0

int main() {
    // Get the singleton instance of UserSettingsParser
    UserSettingsParser& settingsParser = UserSettingsParser::getInstance();

#if SET == 1
    // Create a settings file if it doesn't exist
   settingsParser.createFileIfNotExists("user_settings.conf");

    // Load settings from the file
    settingsParser.loadSettings("user_settings.conf");

    // Set a new value
    settingsParser.setValue("username", "gokul1");
    settingsParser.setValue("username_pass", "123456odicincuine");

    // Save settings back to the file
    settingsParser.saveSettings();
#endif
#if GET == 1
   settingsParser.loadSettings("user_settings.conf");
   std::string data =settingsParser.getValue("username_pass");
   std::cout << data << std::endl;
#endif   
#if SETS == 1
    // Create a settings file if it doesn't exist
   settingsParser.createFileIfNotExists("user_settings.conf");

    // Load settings from the file
    settingsParser.loadSettings("user_settings.conf");

    // Set a new value
    settingsParser.setValueAs("one", 87238753);
    settingsParser.setValueAs("two", 872531181);

    // Save settings back to the file
    settingsParser.saveSettings();
#endif
#if GETS == 1
    // Create a settings file if it doesn't exist
   settingsParser.createFileIfNotExists("user_settings.conf");

    // Load settings from the file
    settingsParser.loadSettings("user_settings.conf");

    // Set a new value
   int data =settingsParser.getValueAs<double>("one");
   std::cout << data << std::endl;
   data =settingsParser.getValueAs<double>("two");
   std::cout << data << std::endl;

    // Save settings back to the file
    settingsParser.saveSettings();
#endif
    return 0;
}
