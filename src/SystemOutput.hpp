#ifndef SYSTEM_OUTPUT_H
#define SYSTEM_OUTPUT_H

#include <string>

void print_menu(int context = 0);
void print_key(std::string &outStr);
void write_file_key(std::string &outStr, std::string &filename);

#endif