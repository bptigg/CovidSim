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
		{
			ScenarioFile << std::endl << "Bus Network" << std::endl;
			ScenarioFile << "Number of Bus stops/station" << std::endl;

			std::cout << "Number of Bus stops/station: ";
			std::cin >> Num_Bus_Stops;
			ScenarioFile << Num_Bus_Stops << std::endl;

			for (unsigned int i = 0; i < Num_Bus_Stops; i++)
			{
				std::string input;
				bool NotCorrectInput = true;
				unsigned int staff = 0;

				while (NotCorrectInput)
				{
					ScenarioFile << "Type" << std::endl;
					std::cout << "Type (stop or station): ";
					std::cin >> input;
					if (input == "stop")
					{
						ScenarioFile << '0' << std::endl;
						NotCorrectInput = false;
					}
					else if (input == "station")
					{
						ScenarioFile << '1' << std::endl;
						NotCorrectInput = false;
						std::cout << "Number of staff: ";
						std::cin >> staff;

					}
					else
					{
						Log log(Log::LogLevelWarning);
						log.LogFucntion(Log::LogLevelWarning, 1);
						std::cout << "Incorrect input" << std::endl;
					}
				}

				int x, y, tile_num = 0;

				std::cout << "X coord of the Bus stop (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the Bus stop (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;

				ScenarioFile << "Bus_stop " << (i + 1) << std::endl;
				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				std::pair<int, std::pair<int, int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_Bus_Stops, Num_Bus_Stops);
			std::cout << "Adjaceny matrix to represent the bus network." << std::endl;
			ScenarioFile << "Bus_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_Bus_Stops; i++)
			{
				std::cout << "Bus stop " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << "Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_Bus_Stops; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To Bus stop " << (a + 1) << " at location: " << Transport[a].second.first << " ,  " << Transport[a].second.second << "Tile number: " << Transport[i].first << std::endl << "If so how many counts does it take, if not put 0: ";
						std::cin >> time;
						Adjacency->MatrixEdit(i + 1, a + 1, time);
					}
					else
					{
						Adjacency->MatrixEdit(i + 1, a + 1, 0);
					}
				}
			}
			Adjacency->PrintMat(ScenarioFile);
			delete Adjacency;
		}
		
		Transport.clear();

		{
			ScenarioFile << std::endl << "Train Network" << std::endl;
			ScenarioFile << "Number of Train stations" << std::endl;

			std::cout << "Number of Train stations: ";
			std::cin >> Num_Train_stations;
			ScenarioFile << Num_Train_stations << std::endl;

			for (unsigned int i = 0; i < Num_Train_stations; i++)
			{
				std::string input;
				bool NotCorrectInput = true;
				unsigned int staff = 0;

				while (NotCorrectInput)
				{
					ScenarioFile << "Type" << std::endl;
					std::cout << "Type local or regional: ";
					std::cin >> input;
					if (input == "local")
					{
						ScenarioFile << '0' << std::endl;
						NotCorrectInput = false;
					}
					else if (input == "regional")
					{
						ScenarioFile << '1' << std::endl;
						NotCorrectInput = false;
					}
					else
					{
						Log log(Log::LogLevelWarning);
						log.LogFucntion(Log::LogLevelWarning, 1);
						std::cout << "Incorrect input" << std::endl;
					}
				}

				int x, y, tile_num = 0;

				std::cout << "X coord of the train station (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the train station (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;
				std::cout << "Nunber of staff: ";
				std::cin >> staff;

				ScenarioFile << "Train_station  " << (i + 1) << std::endl;
				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				std::pair<int, std::pair<int , int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_Train_stations, Num_Train_stations);
			std::cout << "Adjaceny matrix to represent the train network." << std::endl;
			ScenarioFile << "Train_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_Bus_Stops; i++)
			{
				std::cout << "Train station " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << "Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_Bus_Stops; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To train station " << (a + 1) << " at location: " << Transport[a].second.first << " ,  " << Transport[a].second.second << "Tile number: " << Transport[i].first << std::endl << "If so how many counts does it take, if not put 0: ";
						std::cin >> time;
						Adjacency->MatrixEdit(i + 1, a + 1, time);
					}
					else
					{
						Adjacency->MatrixEdit(i + 1, a + 1, 0);
					}
				}
			}
			Adjacency->PrintMat(ScenarioFile);
			delete Adjacency;
		}

		Transport.clear();

		{
			ScenarioFile << "Airports" << std::endl;
			ScenarioFile << "Number_of_airports" << std::endl;

			std::cout << "Number of airports: ";
			std::cin >> Num_airports;
			ScenarioFile << Num_airports << std::endl;

			for (unsigned int i = 0; i < Num_airports; i++)
			{
				std::string input;
				bool NotCorrectInput = true;
				unsigned int staff;

				while (NotCorrectInput)
				{
					ScenarioFile << "Type" << std::endl;
					std::cout << "Type domestic or international: ";
					std::cin >> input;
					if (input == "domestic")
					{
						ScenarioFile << '0' << std::endl;
						NotCorrectInput = false;
					}
					else if (input == "international")
					{
						ScenarioFile << '1' << std::endl;
						NotCorrectInput = false;
					}
					else
					{
						Log log(Log::LogLevelWarning);
						log.LogFucntion(Log::LogLevelWarning, 1);
						std::cout << "Incorrect input" << std::endl;
					}
				}

				int x, y, tile_num = 0;

				std::cout << "X coord of the Airport (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the Airport (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;
				std::cout << "Number of staff: ";
				std::cin >> staff;

				ScenarioFile << "Airport  " << (i + 1) << std::endl;
				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				std::system("CLS");
			}
		}

		Transport.clear();

		{
			ScenarioFile << std::endl << "Metro Network" << std::endl;
			ScenarioFile << "Number of Metro stations" << std::endl;

			std::cout << "Number of Metro stations: ";
			std::cin >> Num_Train_stations;
			ScenarioFile << Num_metro_stations << std::endl;

			for (unsigned int i = 0; i < Num_Train_stations; i++)
			{
				int x, y, tile_num = 0;

				std::cout << "X coord of the Metro station (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the Metro station (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;

				ScenarioFile << "Metro_station  " << (i + 1) << std::endl;
				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << std::endl;

				std::pair<int, std::pair<int, int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_metro_stations, Num_metro_stations);
			std::cout << "Adjaceny matrix to represent the Metro network." << std::endl;
			ScenarioFile << "Metro_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_Bus_Stops; i++)
			{
				std::cout << "Metro station " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << "Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_Bus_Stops; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To Metro station " << (a + 1) << " at location: " << Transport[a].second.first << " ,  " << Transport[a].second.second << "Tile number: " << Transport[a].first << std::endl << "If so how many counts does it take, if not put 0: ";
						std::cin >> time;
						Adjacency->MatrixEdit(i + 1, a + 1, time);
					}
					else
					{
						Adjacency->MatrixEdit(i + 1, a + 1, 0);
					}
				}
			}
			Adjacency->PrintMat(ScenarioFile);
			delete Adjacency;
		}

		Transport.clear();
		std::system("CLS");

		ScenarioFile << "Scenario_Infomation" << std::endl;
		ScenarioFile << "Population_data" << std::endl;
		ScenarioFile << "Population" << std::endl;
		std::cout << "Population: ";
		std::cin >> population;

		Population_Pyramid* age_data = new Population_Pyramid;
		
		std::cout << "Population Pyramid (%)" << std::endl;
		ScenarioFile << "Population_Pyramind_(%)" << std::endl;

		std::cout << "0-4 (%): ";
		std::cin >> age_data->zero_to_four;
		std::cout << "5-17 (%): ";
		std::cin >> age_data->five_to_seventeen;
		std::cout << "18-49 (%): ";
		std::cin >> age_data->eighteen_to_fourty_nine;
		std::cout << "50-64(%): ";
		std::cin >> age_data->fifty_to_sixty_four;
		std::cout << "65+ (%): ";
		std::cin >> age_data->sixty_five_plus;

		ScenarioFile << age_data->zero_to_four << std::endl << age_data->five_to_seventeen << std::endl << age_data->eighteen_to_fourty_nine << std::endl << age_data->five_to_seventeen << std::endl << age_data->sixty_five_plus << std::endl;
		delete age_data;

		std::system("CLS");

		Population_race_data* race_data = new Population_race_data;

		std::cout << "Population race data (%)" << std::endl;
		ScenarioFile << "Population_race_data (%)" << std::endl;
		
		std::cout << "Non-Hispanic White (%): ";
		std::cin >> race_data->white;
		std::cout << "Non-Hispanic Black (%): ";
		std::cin >> race_data->black;
		std::cout << "Hispanic (%): ";
		std::cin >> race_data->hispanic;
		std::cout << "other (%): ";
		std::cin >> race_data->other;

		ScenarioFile << race_data->white << std::endl << race_data->black << std::endl << race_data->hispanic << std::endl << race_data->other << std::endl;
		delete race_data;

		std::system("CLS");

		Medical_data* child_data = new Medical_data;

		std::cout << "Medical data for children (%)" << std::endl;
		ScenarioFile << "Child_medical_data (%)" << std::endl;

		std::cout << "Asthma (%): ";
		std::cin >> child_data->Asthma;
		std::cout << "Auto immune disease (%): ";
		std::cin >> child_data->Auto_immune_disease;
		std::cout << "Cardiovascular disease (%): ";
		std::cin >> child_data->Cardiovascular_disease;
		std::cout << "Chronic lung disease (%): ";
		std::cin >> child_data->chronic_lung_disease;
		std::cout << "Gastrointestial/liver disease (%): ";
		std::cin >> child_data->Gastrointestinal_liver_disease;
		std::cout << "Hypertension (%): ";
		std::cin >> child_data->Hypertension;
		std::cout << "Immune suppresion (%): ";
		std::cin >> child_data->Immune_disease;
		std::cout << "Metabolic disease (%): ";
		std::cin >> child_data->Metabolic_disease;
		std::cout << "Neurological disease (%): ";
		std::cin >> child_data->Neurological_disease;
		std::cout << "Obesity (%): ";
		std::cin >> child_data->Obesity;
		std::cout << "Renal disease (%): ";
		std::cin >> child_data->Renal_disease;
		std::cout << "Other disease (%): ";
		std::cin >> child_data->other_disease;
		std::cout << "No known disease (%): ";
		std::cin >> child_data->no_known_disease;

		ScenarioFile << child_data->Asthma << std::endl << child_data->Auto_immune_disease << std::endl << child_data->Cardiovascular_disease << std::endl << child_data->chronic_lung_disease << std::endl << child_data->Gastrointestinal_liver_disease << std::endl << child_data->Hypertension << std::endl << child_data->Immune_disease << std::endl << child_data->Metabolic_disease << std::endl << child_data->Neurological_disease << std::endl << child_data->Obesity << std::endl << child_data->Renal_disease << std::endl << child_data->other_disease << std::endl << child_data->no_known_disease << std::endl;
		delete child_data;

		std::system("CLS");

		Medical_data* adult_data = new Medical_data;

		std::cout << "Medical data for adults (%)" << std::endl;
		ScenarioFile << "Adult_medical_data";

		std::cout << "Asthma (%): ";
		std::cin >> adult_data->Asthma;
		std::cout << "Auto immune disease (%): ";
		std::cin >> adult_data->Auto_immune_disease;
		std::cout << "Cardiovascular disease (%): ";
		std::cin >> adult_data->Cardiovascular_disease;
		std::cout << "Chronic lung disease (%): ";
		std::cin >> adult_data->chronic_lung_disease;
		std::cout << "Gastrointestial/liver disease (%): ";
		std::cin >> adult_data->Gastrointestinal_liver_disease;
		std::cout << "Hypertension (%): ";
		std::cin >> adult_data->Hypertension;
		std::cout << "Immune suppresion (%): ";
		std::cin >> adult_data->Immune_disease;
		std::cout << "Metabolic disease (%): ";
		std::cin >> adult_data->Metabolic_disease;
		std::cout << "Neurological disease (%): ";
		std::cin >> adult_data->Neurological_disease;
		std::cout << "Obesity (%): ";
		std::cin >> adult_data->Obesity;
		std::cout << "Renal disease (%): ";
		std::cin >> adult_data->Renal_disease;
		std::cout << "Other disease(%): ";
		std::cin >> adult_data->other_disease;
		std::cout << "No known disease (%): ";
		std::cin >> adult_data->no_known_disease;

		ScenarioFile << adult_data->Asthma << std::endl << adult_data->Auto_immune_disease << std::endl << adult_data->Cardiovascular_disease << std::endl << adult_data->chronic_lung_disease << std::endl << adult_data->Gastrointestinal_liver_disease << std::endl << adult_data->Hypertension << std::endl << adult_data->Immune_disease << std::endl << adult_data->Metabolic_disease << std::endl << adult_data->Neurological_disease << std::endl << adult_data->Obesity << std::endl << adult_data->Renal_disease << std::endl << adult_data->other_disease << std::endl << adult_data->no_known_disease << std::endl;
		delete adult_data;

		std::system("CLS");

		Scenario_Parameters* param = new Scenario_Parameters;

		std::cout << "Scenario critical data" << std::endl;
		ScenarioFile << "Scenario parameters" << std::endl;

		std::cout << "Number of counts: ";
		std::cin >> param->count;
		std::cout << "Output file name: ";
		std::cin >> param->Output_file_name;
		
		std::cout << std::endl << "Data to output" << std::endl;
		ScenarioFile << "Output_Data" << std::endl;

		std::cout << "With these following question's awnser (yes/no): " << std::endl;

		param->R0 = Input("R0");
		param->Suceptable = Input("Suceptable");
		param->Infected = Input("Infected");
		param->Recovered = Input("Recovered");
		param->Hostipilized = Input("Hostipilized");
		param->Dead = Input("Dead");
		param->mortality_rate = Input("Mortality");
		param->morbidity_rate = Input("Morbidity");

		ScenarioFile << param->R0 << std::endl << param->Suceptable << std::endl << param->Infected << std::endl << param->Recovered << std::endl << param->Hostipilized << std::endl << param->Dead << std::endl << param->mortality_rate << std::endl << param->morbidity_rate << std::endl << std::endl;
		delete param;

		Social_Distance_poll* policy = new Social_Distance_poll;

		std::cout << "Social Distancing policys (check documentaion for what they are)." << std::endl;
		std::cout << "% of population that has Covid at which they become active" << std::endl;
		ScenarioFile << "Social_Distance_policies" << std::endl;

		std::cout << "Level 1 (%): ";
		std::cin >> policy->L1;
		std::cout << "Level 2 (%): ";
		std::cin >> policy->L2;
		std::cout << "Level 3 (%): ";
		std::cin >> policy->L3;
		std::cout << "Level 4 (%): ";
		std::cin >> policy->L4;
		std::cout << "Level 5 (%): ";
		std::cin >> policy->L5;
		std::cout << "Level 6 (%): ";
		std::cin >> policy->L6;
		std::cout << "Level 7 (%): ";
		std::cin >> policy->L7;

		ScenarioFile << policy->L1 << std::endl << policy->L2 << std::endl << policy->L3 << std::endl << policy->L4 << std::endl << policy->L5 << std::endl << policy->L6 << std::endl << policy->L7 << std::endl << std::endl;
		delete policy;
	}
	ScenarioFile.close();

	std::cout << "Data to written file successfully" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Scenario::csc(std::ofstream &Scenariofile, const std::string type, unsigned int number)
{
	std::cout << "Number of " << type << "s: ";
	std::cin >> number;

	Scenariofile << number << std::endl << std::endl;

	for (unsigned int i = 0; i < number; i++)
	{
		int x, y = 0;
		unsigned int tile_num, capacity, staff = 0;

		std::cout << type << " " << i << std::endl;

		std::cout << "X coord of the " << type << " (0 being the bottom left corner): ";
		std::cin >> x;
		std::cout << "Y coord of the " << type << " (0 being the bottom left corner): ";
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

int Scenario::Input(std::string param)
{
	Log log(Log::LogLevelWarning);
	std::string Input;
	bool CorrectInput = false;

	while (CorrectInput == false)
	{
		std::cout << param << " : ";
		std::cin >> Input;

		if (Input == "yes")
		{
			CorrectInput = true;
			return 1;
		}
		else if (Input == "no")
		{
			CorrectInput = true;
			return 0;
		}
		else
		{
			std::cout << std::endl <<  "Incorrect Input" << std::endl;
			log.LogFucntion(Log::LogLevelWarning, 1);
		}
	}
	return NULL;
}

void Scenario::ScenarioCreate()
{
	//This could be a feature, probably write after the main model. 
}

void Scenario::CreateModel()
{
	//Prety self explanitory 
}

