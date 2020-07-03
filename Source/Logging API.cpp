#include "Logging API.h"

Log::Log(LogLevel level)
	:m_CurrentLevel(level)
{
	Recorded.clear();
}

Log::~Log()
{
	std::ofstream LogFile("LogFile");

	if (LogFile.is_open())
	{
		for (auto elem : Recorded)
		{
			switch (m_CurrentLevel)
			{
			case 1:
				LogFile << "[INFO]" << " " << "[" << elem.first.second << "]" << elem.second << std::endl;
				break;
			case 2:
				LogFile << "[WARNING]" << " " << "[" << elem.first.second << "]" << elem.second << std::endl;
				break;
			case 3:
				LogFile << "[ERROR]" << " " << "[" << elem.first.second << "]" << elem.second << std::endl;
				break;
			case 4:
				LogFile << "[CRTICAL ERROR]" << " " << "[" << elem.first.second << "]" << elem.second << std::endl;
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

	if (m_CurrentLevel == 1)
	{
		std::map<unsigned int, std::string>::iterator temp = Info.find(ErrorNumber);
		Recorded.insert({ ErrorType, temp->second });
	}
	else if (m_CurrentLevel == 2)
	{
		std::map<unsigned int, std::string>::iterator temp = Warning.find(ErrorNumber);
		Recorded.insert({ ErrorType, temp->second });
	}
	else if (m_CurrentLevel == 3)
	{
		std::map<unsigned int, std::string>::iterator temp = Error.find(ErrorNumber);
		Recorded.insert({ ErrorType, temp->second });
	}
	else if (m_CurrentLevel == 4)
	{
		std::map<unsigned int, std::string>::iterator temp = CriticalError.find(ErrorNumber);
		Recorded.insert({ ErrorType, temp->second });
	}
}

