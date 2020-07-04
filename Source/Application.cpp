#include <iostream>

#include "Menu.h"
#include "Logging API.h"

int main()
{
	std::cout << "Build Number: " << "[ 1 ]" << " Build Date: " << "02/07/2020" << std::endl;
	
	Menu menu(0);
	menu.DisplayMainMenu(); //here for test purposes

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