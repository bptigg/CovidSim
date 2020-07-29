#pragma once
#include <iostream>

#include "Logging API.h"
#include "Scenario.h"

class Menu
{
private:
	unsigned int m_Choice = 0;
	bool CorrectMenuInput = false;
public:
	Menu(int Default);
	~Menu();
	
	unsigned int DisplayMainMenu();
};