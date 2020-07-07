#include "Menu.h"

Menu::Menu(int Default)
	:m_Choice(Default)
{
	CorrectMenuInput = false;
}

Menu::~Menu()
{
}

unsigned int Menu::DisplayMainMenu()
{
	Log logMenu(Log::LogLevelInfo);

	while (CorrectMenuInput == false)
	{
		std::cout << "1). Import Scenario " << std::endl;
		std::cout << "2). Create Scenario " << std::endl; // MAY NOT GET TO
		std::cout << "3). Run Random Scenario " << std::endl; //
		std::cout << "4). Quit " << std::endl;
		std::cin >> m_Choice;

		switch (m_Choice)
		{
		case 1:
			std::cout << "Import Scenario not available" << std::endl;
			CorrectMenuInput = true;
			break;
		case 2:
			std::cout << "Create Scenario not available" << std::endl;
			CorrectMenuInput = true;
			break;
		case 3:
			std::cout << "Run Random Scenario not available" << std::endl;
			CorrectMenuInput = true;
			break;
		case 4:
			CorrectMenuInput = true;
			exit(0);
			break;
		default:
			std::cout << "Incorrect Input" << std::endl;
			logMenu.LogFucntion(Log::LogLevelInfo, 1);
			
		}; 
	}
	return  m_Choice;
}

