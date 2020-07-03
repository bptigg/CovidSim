#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

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

	std::map<unsigned int, std::string> Info;
	std::map<unsigned int, std::string> Warning;
	std::map<unsigned int, std::string > Error;
	std::map<unsigned int, std::string> CriticalError;

	std::map<std::pair<LogLevel, int>, std::string> Recorded;

public:
	Log(LogLevel level);
	~Log();

	void LogFucntion(LogLevel level, unsigned int ErrorNumber);


};

