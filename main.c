#include "UserSettingsParserWrapper.h"
#include <stdio.h>

int main() {
    const char* filename = "settings.txt";

    create_file_if_not_exists(filename);
    load_settings(filename);

    set_value("username", "gokul");
    set_value_as_int("age", 30);
    set_value_as_bool("is_admin", 1);

    printf("Username: %s\n", get_value("username"));
    printf("Age: %d\n", get_value_as_int("age"));
    printf("Is Admin: %d\n", get_value_as_bool("is_admin"));

    save_settings();
    printf("tmp flag : %s\n", get_usr_config_path());

    return 0;
}

