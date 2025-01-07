#ifndef USER_SETTINGS_PARSER_WRAPPER_H
#define USER_SETTINGS_PARSER_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void create_file_if_not_exists(const char* filename);
void load_settings(const char* filename);
const char* get_value(const char* key);
int get_value_as_int(const char* key);
double get_value_as_double(const char* key);
int get_value_as_bool(const char* key);
void set_value(const char* key, const char* value);
void set_value_as_int(const char* key, int value);
void set_value_as_double(const char* key, double value);
void set_value_as_bool(const char* key, int value);
void save_settings();
void save_settings_as(const char* filename);
const char* get_usr_config_path(void);
const char* get_wifi_config_path(void);

#ifdef __cplusplus
}
#endif
#endif
