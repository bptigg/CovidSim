#include "Scenario.h"

Scenario::Scenario(const std::string &filename, unsigned int mode )
	:m_mode(mode)
{
	m_filepath.append(filename);
}

Scenario::Scenario(unsigned int mode)
	: m_mode(mode)
{
}

Scenario::~Scenario()
{
}

void Scenario::ScenarioImport()
{
	bool FileFound = false;
	std::ifstream ScenarioFile;
	std::filesystem::path filepath = m_filepath;
	
	ScenarioFile.open(m_filepath);

	while (FileFound == false)
	{
		if (ScenarioFile.is_open())
		{
			if (filepath.extension() == ".cvsn")
			{
				//write some code here when i know what the perameters will be
				ScenarioFile.close();
			}
			else
			{
				std::cout << "Wrong filepath" << std::endl;
				{
					Log logScenario(Log::LogLevelInfo);
					logScenario.LogFucntion(Log::LogLevelWarning, 1);
				}
			}
		}
		else if (ScenarioFile.fail())
		{
			std::cout << "File not Found" << std::endl;
			{
				Log log(Log::LogLevelInfo);
				log.LogFucntion(Log::LogLevelCriticalError, 1);
			}
		}
	}
}

void Scenario::ScenarioEditor()
{
	std::string file;
	bool File_exists = true;

	Log logScenarioEditor(Log::LogLevelInfo);
	std::ofstream ScenarioFile;

	while (File_exists)
	{
		std::cout << "Input filename: ";
		std::cin >> file;

		std::ifstream temp;
		temp.open("Scenarios/" + file + ".cvsn");
		
		if (temp.fail())
		{
			File_exists = false;
		}
		else
		{
			logScenarioEditor.LogFucntion(Log::LogLevelInfo, 2);

			char choice;
			std::cout << "File with name: " << file << " already exists" << std::endl;
			std::cout << "Do you wish to overwrite this file, (Y)es or (N)o: ";
			std::cin >> choice;

			if (choice == 'Y' || choice == 'y')
			{
				File_exists = false;
			}
			else
			{
				File_exists = true;

			}

			temp.close();
		}
	}

	ScenarioFile.open("Scenarios/" + file + ".cvsn");
	//write some code here when I know what the parameters are
	ScenarioFile.close();
}

void Scenario::ScenarioCreate()
{
	//This could be a feature, probably write after the main model. 
}

void CreateModel()
{
	//Prety self explanitory 
}

