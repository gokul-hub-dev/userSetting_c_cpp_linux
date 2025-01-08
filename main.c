#include "UserSettingsParserWrapper.h"
#include <stdio.h>
#include <stdbool.h>
int main() {
    const char* filename = "settings.txt";

    //create_file_if_not_exists(filename);
    int ret=load_settings(filename);
    if(ret==-1)
    {
        printf("Error loading settings\n");
        return -1;
    }
    //set_value("username", "gokul");
    //set_value_as_int("age", 30);
    //set_value_as_bool("is_admin", 1);
    bool ret1=0;
    ret1=get_value_as_bool("status");
    if(ret1==1)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAILURE\n");
    }
    printf("Username: %s\n", get_value("username"));
    printf("Age: %d\n", get_value_as_int("age"));
    printf("status: %d\n", get_value_as_bool("status"));

    save_settings();

    return 0;
}
