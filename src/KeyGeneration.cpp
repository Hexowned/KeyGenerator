#include "KeyGeneration.hpp"

#include "InputValidation.hpp"

#include <iostream>
#include <random>

/* Returns a validated boolean*/
bool want(const std::string &greeting, const std::string &sorry)
{
	std::cout << greeting << '\n';
	while (true)
	{
		char userChoice = validate_character("You did not enter an alphabetical character.\n");
		if (userChoice == 'y')
		{
			return true;
		}
		else if (userChoice == 'n')
		{
			return false;
		}

		std::cout << sorry;
	}
}

/*
Generates a random string based on user's length specifications.
Returns true if successful
*/
std::string generate_key(std::string &alphabet, int length)
{
	// RNG to generate a character
	std::random_device rd;
	std::mt19937 valueGenerator(rd());
	std::uniform_int_distribution<> dist(0, alphabet.size() - 1);

	// Create key using all the available characters
	std::string Key;
	int codeValue = 0;
	for (unsigned i = 0; i < length; i++)
	{
		codeValue = (dist(valueGenerator));
		Key.push_back(alphabet.at(codeValue));
		// std::cout << alphabet.at(codeValue) << '\n';
	}

	encode_key(Key);
	return Key;
}

// Simple ceasar cipher to encode key
void encode_key(std::string &key)
{
	int offset = 3;
	for (auto &x : key)
	{
		x += offset;
	}
}

std::string make_alphabet()
{
	static const std::string upper_case_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const std::string lower_case_letters = "abcdefghijklmnopqrstuvwxyz";
	static const std::string numbers = "0123456789";
	static const std::string special_characters = "!@#$%^&*()_+-=;':\",./<>?~`";

	std::string alphabet;
	int strLength = get_int(1, std::numeric_limits<char>::max(), "Enter key length within range", "You are out of range");
	if (want("Do you want to include uppercase letters?", "Invalid character input, please try again\n")) alphabet += upper_case_letters;
	if (want("Do you want to include lowercase letters?", "Invalid character input, please try again\n")) alphabet += lower_case_letters;
	if (want("Do you want to include special characters?", "Invalid character input, please try again\n")) alphabet += special_characters;
	if (want("Do you want to include numbers?", "Invalid character input, please try again\n")) alphabet += numbers;

	if (alphabet.empty())
	{
		std::cerr << "Looks like I can't complete your request\n";
		return alphabet;
	}

	return generate_key(alphabet, strLength);
}