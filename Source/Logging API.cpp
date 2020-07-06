#include "Logging API.h"

Log::Log(LogLevel level)
	:m_CurrentLevel(level)
{
	Recorded.clear();
}

Log::~Log()
{
	std::fstream LogFile;
	LogFile.open("Logfile.txt", std::ios::out | std::ios::app);

	if (LogFile.is_open())
	{
		for (auto elem : Recorded)
		{
			switch (elem.first.first)
			{
			case 0:
				LogFile << "[INFO]" << " " << "[" << elem.first.second << "] " << elem.second << std::endl;
				break;
			case 1:
				LogFile << "[WARNING]" << " " << "[" << elem.first.second << "] " << elem.second << std::endl;
				break;
			case 2:
				LogFile << "[ERROR]" << " " << "[" << elem.first.second << "] " << elem.second << std::endl;
				break;
			case 3:
				LogFile << "[CRTICAL ERROR]" << " " << "[" << elem.first.second << "] " << elem.second << std::endl;
				break;
			default:
				LogFile << "[CRITICAL ERROR]" << "Seems we have a bit of an error here, don't worry it will be fixed soon" << std::endl;
				break;
			}
		}
	}

	LogFile.close();
}

void Log::LogFucntion(LogLevel level, unsigned int ErrorNumber)
{
	m_CurrentLevel = level;
	
	std::pair <LogLevel, unsigned int> ErrorType;
	ErrorType.first = level;
	ErrorType.second = ErrorNumber;

	if (m_CurrentLevel == 0)
	{
		std::map<unsigned int, std::string>::iterator temp = Info.find(ErrorNumber);
		Recorded.insert(std::make_pair(ErrorType, temp->second));
	}
	else if (m_CurrentLevel == 1)
	{
		std::map<unsigned int, std::string>::iterator temp = Warning.find(ErrorNumber);
		Recorded.insert(std::make_pair(ErrorType, temp->second));
	}
	else if (m_CurrentLevel == 2)
	{
		std::map<unsigned int, std::string>::iterator temp = Error.find(ErrorNumber);
		Recorded.insert(std::make_pair(ErrorType, temp->second));
	}
	else if (m_CurrentLevel == 3)
	{
		std::map<unsigned int, std::string>::iterator temp = CriticalError.find(ErrorNumber);
		Recorded.insert(std::make_pair(ErrorType, temp->second));
	}
}

void Log::Clear()
{
	std::ofstream LogFile;
	LogFile.open("Logfile.txt", std::ios::out | std::ios::trunc);
	LogFile.close();
}

void NewRun()
{
	std::fstream LogFile;
	LogFile.open("Logfile.txt", std::ios::out | std::ios::app);

	LogFile << "----------NEW RUN----------" << std::endl;

	LogFile.close();
}
