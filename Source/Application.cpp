#include <iostream>

#include "Menu.h"
#include "Logging API.h"
#include "Scenario.h"
#include "Matrix.h"
#include "Matrix.cpp"


int main()
{
	{
		Log log(Log::LogLevelInfo);
		log.Clear();
		std::cout << log.GetCurrentTime() << std::endl;
	}
	
	Matrix<int> test(2, 2);
	test.PrintMat();

	Menu menu(0);
	int choice = menu.DisplayMainMenu(); //here for test purposes
	
	if (choice == 2)
	{
		Scenario test;
		test.ScenarioEditor(); //here for test purposes
	}
	/*
	{
		
		Log log(Log::LogLevelInfo);
		log.Clear();
		log.LogFucntion(Log::LogLevelInfo, 1);
		log.LogFucntion(Log::LogLevelWarning, 1);
		log.LogFucntion(Log::LogLevelError, 1);
		log.LogFucntion(Log::LogLevelCriticalError, 1);                                                                          
		//Currently here for log testing purposes
	}

	{
		Log log(Log::LogLevelInfo);
		log.LogFucntion(Log::LogLevelError, 2);
	}
	*/

	std::cin.get();
}