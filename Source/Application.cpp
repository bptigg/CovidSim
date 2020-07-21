#include <iostream>

#include "Menu.h"
#include "Logging API.h"
#include "Scenario.h"

int main()
{
	{
		Log log(Log::LogLevelInfo);
		log.Clear();
		std::cout << log.GetCurrentTime() << std::endl;
	}
	
	Menu menu(0);
	menu.DisplayMainMenu(); //here for test purposes

	Scenario test(1);
	test.ScenarioEditor(); //here for test purposes

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