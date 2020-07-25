#pragma once

#include <iostream>
#include <fstream>
#include <time.h>

#include <string>
#include <map>
#include <tuple>

class Log
{
public:
	enum LogLevel
	{
		LogLevelInfo = 0, LogLevelWarning, LogLevelError, LogLevelCriticalError
	};
private:
	LogLevel m_CurrentLevel;

	std::map<unsigned int, std::string> Info { {1 ,"Info message 1"}, {2, "FILE ALREADY EXISTS"} };
	std::map<unsigned int, std::string> Warning { {1 ,"INCORRECT INPUT"}, {2, "Warning message 2"} };
	std::map<unsigned int, std::string > Error { {1 ,"WRONG FILE EXTENSION"}, {2, "Error message 2"} };
	std::map<unsigned int, std::string> CriticalError { {1 ,"FILE NOT FOUND"}, {2, "Error message 2"} };

	std::map<std::pair<LogLevel, int>, std::string> Recorded;

public:
	Log(LogLevel level);
	~Log();

	void LogFucntion(LogLevel level, unsigned int ErrorNumber);
	void NewRun();
	void Clear();

	std::string GetCurrentTime();


};

