#include "Scenario.h"

Scenario::Scenario(const std::string &filename)
{
	m_filepath.append(filename);
}

Scenario::Scenario()
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
	{
		ScenarioFile << "Scenario_Name: " + file << std::endl << "World_Infomation" << std::endl << std::endl << "Tile_Size(meters)" << std::endl;
		{
			std::cout << "Tile_Size (meters): ";
			std::cin >> tile_size;

			std::cout << "Number of tiles: ";
			std::cin >> Num_Of_Tiles;

			std::cout << "Number of unique buildings (e.g. Hostpitals, restuarants, schools): ";
			std::cin >> Num_Uq_Buildings;

			ScenarioFile << tile_size << std::endl << std::endl << "Num_of_tiles" << std::endl << Num_Of_Tiles << std::endl << std::endl << "Num_of_Unique_Buildings" << std::endl << Num_Uq_Buildings << std::endl << std::endl;
		}
		
		ScenarioFile << "Unique_Buildings" << std::endl << "Public_Services" << std::endl << "Education_buildings" << std::endl;
		ScenarioFile << "Num_of_primary_schools" << std::endl;
		csc(ScenarioFile, "Primary School", Num_of_Primary_Schools);
		csc(ScenarioFile, "Secondry School", Num_of_Secondry_Schools);
		csc(ScenarioFile, "Universities", Num_of_Uni);
		
		ScenarioFile << std::endl << "Public_Services" << std::endl;
		csc(ScenarioFile, "Hospital", Num_of_Hospitals);
		csc(ScenarioFile, "Place of Worship", Num_of_POWs);
		csc(ScenarioFile, "Restuarant", Num_of_Restuarants);
		csc(ScenarioFile, "Cinema", Num_of_Cinemas);
		csc(ScenarioFile, "Shopping center", Num_of_Shopping_Centers);
		csc(ScenarioFile, "Park", Num_of_Parks);

		ScenarioFile << std::endl << "Public_Transport" << std::endl;
	}
	ScenarioFile.close();
}

void Scenario::csc(std::ofstream &Scenariofile, const std::string type, unsigned int number)
{
	std::cout << "Number of " << type << ": ";
	std::cin >> number;

	Scenariofile << number << std::endl << std::endl;

	for (unsigned int i = 0; i < number; i++)
	{
		int x, y = 0;
		unsigned int tile_num, capacity, staff = 0;

		std::cout << "Tile size: " << tile_size << std::endl;
		std::cout << "Number of tiles: " << Num_Of_Tiles << std::endl;

		std::cout << "X coord of the " << type << " (0 being the bottom left corner): ";
		std::cin >> x;
		std::cout << "Y coord of the " << type << " (O being the bottom left corner): ";
		std::cin >> y;
		std::cout << "What tile is the " << type << " on: ";
		std::cin >> tile_num;

		std::cout << "Number of staff in the " << type << " : ";
		std::cin >> staff;

		std::cout << "Capacity of the " << type << " (capacity is greater than the number of staff): ";
		std::cin >> capacity;

		Scenariofile << type << " " << (i + 1) << std::endl;
		Scenariofile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << capacity << std::endl << std::endl;

		std::system("CLS");
	}
}

void Scenario::ScenarioCreate()
{
	//This could be a feature, probably write after the main model. 
}

void Scenario::CreateModel()
{
	//Prety self explanitory 
}

