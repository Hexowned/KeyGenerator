#include "InputValidation.hpp"

#include "KeyGeneration.hpp"
#include "SystemOutput.hpp"

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

void skip_to_int()
{
	// something was found that wasn't an integer
	if (std::cin.fail())
	{
		std::cin.clear();
		// throw away all non digits
		for (char ch; std::cin >> ch;)
		{
			if (std::isdigit(ch) || ch == '=')
			{
				std::cin.unget();
				return;
			}
		}
	}

	std::cout << "No input\n";
}

void process_main_menu()
{
	int choice = get_int(1, 3, "Enter an int in the range", "Choice is out of range");

	switch (choice)
	{
	case 1:
		print_menu(choice);
		process_key_menu();
		break;
	case 2:
		process_input_key();
		break;
	case 3:
		std::cout << "Cya!";
		std::exit(0); // EXIT_SUCCESS
		break;
	default:
		break;
	}
}

void process_key_menu()
{
	int choice = get_int(1, 3, "Enter an int in the range", "Choice is out of range");
	std::string Key;
	std::string ofilename("keys.dat");

	switch (choice)
	{
	case 1:
		Key = make_alphabet();
		print_key(Key);
		break;
	case 2:
		Key = make_alphabet();
		write_file_key(Key, ofilename);
		break;
	case 3:
		Key = make_alphabet();
		print_key(Key);
		write_file_key(Key, ofilename);
		break;
	default:
		break;
	}
}

std::vector<std::string> read_file_key(std::string &name)
{
	std::ifstream input_file(name);
	std::vector<std::string> key_lines(1);
	std::string currentline = "";
	int line = 0;

	if (!input_file)
	{
		std::cerr << "File " << name << " does not exists!\n";
		exit(1); // EXIT_FAILURE
	}

	while (std::getline(input_file, currentline))
	{
		key_lines[line] = currentline;
		line++;
		key_lines.resize(key_lines.size() + 1);
	}

	return key_lines;
}

bool validate_key(std::vector<std::string> &key_lines, std::string &key_to_validate)
{
	for (int i = 0; i < key_lines.size(); i++)
	{
		if (key_lines[i].length() == key_to_validate.length())
		{
			if (key_to_validate == key_lines[i])
			{
				std::cout << "Your key is invalid\n";
				return true;
			}
		}
	}

	std::cerr << "Entered key not found in the data file\n";
	return false;
}

void process_input_key()
{
	std::string user_key;
	std::string key_file_name("keys.dat");
	std::vector<std::string> keys_file(read_file_key(key_file_name));
	std::cout << "Enter the key you want to validate: ";
	std::cin.ignore();
	std::getline(std::cin, user_key);
	validate_key(keys_file, user_key);
}

int get_int(const std::string &sorry)
{
	int n = 0;
	while (true)
	{
		if (std::cin >> n)
		{
			return n;
		}

		std::cout << sorry;
		skip_to_int();
	}
}

int get_int(int low, int high, const std::string &greeting, const std::string &sorry)
{
	std::cout << greeting << ":[" << low << ':' << high << "]\n";
	while (true)
	{
		int n = get_int("Sorry, that was not a number, please enter a valid number and try again\n");

		if (low <= n && n <= high)
		{
			return n;
		}

		std::cout << sorry << ":[" << low << ':' << high << "]\n";
	}
}

char validate_character(const std::string &sorry)
{
	char userChoice = ' ';
	while (true)
	{
		if (std::cin >> userChoice)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (std::isalpha(userChoice))
			{
				if (std::isupper(userChoice))
				{
					std::tolower(userChoice);
					return userChoice;
				}

				return userChoice;
			}
		}

		std::cout << sorry;
	}
}