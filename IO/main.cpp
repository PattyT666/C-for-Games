#include <iostream>
#include <string>
#include <limits>

int main()
{
	std::string name = "Patty";
	int age = 51;

	std::cout << "What is your name?" << std::endl;
	std::cin >> name;

	std::cout << "What is your age?" << std::endl;
	std::cin >> age;

	if (std::cin.fail())
	{
		std::cout << "ERROR: I expected a number." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> age;
	}

	if (age < 25)
	{
		std::cout << "Hello " << name << ", you are only " << age << " years old." << std::endl;
	}
	else if (age >= 25 && age < 50)
	{
		std::cout << "Hello " << name << ", you are already " << age << " years old." << std::endl;
	}
	else
	{
		std::cout << "Hello " << name << ". You are very wise for your age." << std::endl;
	}
	std::cout << "Press enter to continue..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}