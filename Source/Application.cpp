#include <iostream>

#include "Menu.h"

int main()
{
	std::cout << "Build Number: " << "[ 1 ]" << " Build Date: " << "02/07/2020" << std::endl;
	
	Menu menu(0);
	menu.DisplayMainMenu(); //here for test purposes

	std::cin.get();
}