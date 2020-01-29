#include "SystemOutput.hpp"

#include <iostream>
#include <fstream>

void print_menu(int context)
{
	switch (context)
	{
	case 0:
		std::cout
			<< "KEY GENERATOR/VALIDATOR\n"
			<< "	MAIN MENU\n"
			<< "1. Generate new key\n"
			<< "2. Validate a key from file\n"
			<< "3. Exit\n";
		break;
	case 1:
		std::cout
			<< "OPTIONS\n"
			<< "1. Print key to screen.\n"
			<< "2. Write key to a file.\n"
			<< "3. Print key and write it to a file.\n";
		break;
	default:
		break;
	}
}

void print_key(std::string &outStr)
{
	std::cout << "Generated code: ";
	int keyLength = outStr.length();

	for (unsigned i = 0; i < keyLength; i += 4)
	{
		std::cout << outStr.substr(i, 4) << ' ';
	}

	std::cout << std::endl;
}

void write_file_key(std::string &outStr, std::string &filename)
{
	std::ofstream out_file(filename, std::ios::binary | std::ios::app);
	int keyLength = outStr.length();
	std::cout << "Writing key to file\n";

	out_file << outStr << '\n';
	std::cout << "File has been successfully written!\n";
	out_file.close();
}