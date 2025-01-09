#include "UserSettingsParserWrapper.h"
#include <stdio.h>
#include <stdbool.h>
int main() {
    int ret;
	ret=create_file_if_not_exists("non_secure.txt");
	if(ret==-1)
    {
        printf("Error Unable to create cvr config settings file\n");
        return -1;
    }
	ret=create_file_if_not_exists("secure.txt");
	if(ret==-1)
    {
        printf("Error Unable to create secure cvr config settings file\n");
        return -1;
    }
	ret=load_settings("secure.txt");
	if(ret==-1)
    {
        printf("Error loading settings\n");
        return -1;
    }
	set_value("secure1", "1");
    set_value("secure2", "2");
	save_settings();

	ret=load_settings("non_secure.txt");
	if(ret==-1)
    {
        printf("Error loading settings\n");
        return -1;
    }
	set_value("non_secure1", "1");
    set_value("non_secure2", "2");
	save_settings();

	ret=load_settings("secure.txt");
	if(ret==-1)
    {
        printf("Error loading settings\n");
        return -1;
    }
	const char* value = get_value("secure1");
    printf("value secure1: %s\n", value);
    value = get_value("secure2");
    printf("value secure2: %s\n", value);

	ret=load_settings("non_secure.txt");
	if(ret==-1)
    {
        printf("Error loading settings\n");
        return -1;
    }
	value = get_value("non_secure1");
    printf("value non_secure1: %s\n", value);
    value = get_value("non_secure2");
    printf("value non_secure2: %s\n", value);
	
    return 0;
}
