#include <iostream>

#include "Menu.h"
#include "Logging API.h"
//#include "Scenario.h"
//#include "Matrix.h"


int main()
{
	{
		Log log(Log::LogLevelInfo);
		//log.Clear();
		std::cout << log.GetCurrentTime() << std::endl;
	}

	Menu main_menu(0);
	main_menu.DisplayMainMenu();

	//Menu menu(0);
	//menu.DisplayMainMenu();

	//std::string input = "test.cvsn";
	//Scenario test(input);
	//test.ScenarioImport();
	
	/*
	Matrix<int>* test = new Matrix<int>(2, 2);
	test->PrintMat();
	delete test;

	Matrix<int> test1(3,3);
	test1.MatrixEdit(2, 1, 3);
	test1.PrintMat();
	test1.GetRow(2);
	test1.GetCol(1);
	test1.PrintMat();

	Menu menu(0);
	menu.DisplayMainMenu(); //here for test purposes
	*/

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