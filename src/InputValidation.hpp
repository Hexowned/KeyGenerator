#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <vector>
#include <string>

void skip_to_int();
void process_main_menu();
void process_key_menu();
std::vector<std::string> read_file_key(std::string &name);
bool validate_key(std::vector<std::string> &key_lines, std::string &key_to_validate);
void process_input_key();
int get_int(int low, int high, const std::string &greeting, const std::string &sorry);
char validate_character(const std::string &sorry);

#endif