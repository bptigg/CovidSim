#pragma once
#include <iostream>

class Menu
{
private:
	unsigned int m_Choice = 0;
	bool CorrectMenuInput = false;
public:
	Menu(int Default);
	~Menu();
	
	void DisplayMainMenu();
};