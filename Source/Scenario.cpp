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

int Scenario::ScenarioImport(World_Infomation& infomation, Population_Pyramid& Population, Population_race_data& race_data, Medical_data& child, Medical_data& adult, Scenario_Parameters& param, Social_Distance_poll& policies)
{
	std::ifstream ScenarioFile;
	std::filesystem::path filepath = m_filepath;

	ScenarioFile.open(m_filepath);

	Log logScenario(Log::LogLevelInfo);
	if (ScenarioFile.is_open())
	{
		if (filepath.extension() == ".cvsn")
		{
			std::cout << "File found" << std::endl;
			logScenario.LogFucntion(Log::LogLevelInfo, 1);
		}
		else
		{
			std::cout << "Wrong filepath" << std::endl;
			{
				logScenario.LogFucntion(Log::LogLevelError, 1);
			}
		}
	}
	else if (ScenarioFile.fail())
	{
		std::cout << "File not Found" << std::endl;
		{
			logScenario.LogFucntion(Log::LogLevelCriticalError, 1);
			return 0;
		}
	}

	tile_size = SingleVar("Tile_Size(meters)", ScenarioFile, tile_size);
	Num_Of_Tiles = SingleVar("Num_of_tiles", ScenarioFile, Num_Of_Tiles);

	Num_Uq_Buildings = SingleVar("Num_of_Unique_Buildings", ScenarioFile, Num_Uq_Buildings);
	Num_of_Primary_Schools = SingleVar("Num_of_Primary Schools", ScenarioFile, Num_of_Primary_Schools);
	Num_of_Secondry_Schools = SingleVar("Num_of_Secondry Schools", ScenarioFile, Num_of_Secondry_Schools);
	Num_of_Uni = SingleVar("Num_of_Universities", ScenarioFile, Num_of_Uni);
	Num_of_Hospitals = SingleVar("Num_of_Hospitals", ScenarioFile, Num_of_Hospitals);
	Num_of_POWs = SingleVar("Num_of_Places of Worship", ScenarioFile, Num_of_POWs);
	Num_of_Restuarants = SingleVar("Num_of_Restuarants", ScenarioFile, Num_of_Restuarants);
	Num_of_Cinemas = SingleVar("Num_of_Cinemas", ScenarioFile, Num_of_Cinemas);
	Num_of_Shopping_Centers = SingleVar("Num_of_Shopping centers", ScenarioFile, Num_of_Shopping_Centers);
	Num_of_Parks = SingleVar("Num_of_Parks", ScenarioFile, Num_of_Parks);

	Num_Bus_Stops = SingleVar("Number of Bus stops/station", ScenarioFile, Num_Bus_Stops);
	Num_Train_stations = SingleVar("Number of Train stations", ScenarioFile, Num_Train_stations);
	Num_airports = SingleVar("Number_of_airports", ScenarioFile, Num_airports);
	Num_metro_stations = SingleVar("Number of Metro stations", ScenarioFile, Num_metro_stations);

	infomation.Primary_school = cscImport("Primary Schools", ScenarioFile, Num_of_Primary_Schools);
	infomation.Secondry_school = cscImport("Secondry Schools", ScenarioFile, Num_of_Secondry_Schools);
	infomation.University = cscImport("Universities", ScenarioFile, Num_of_Uni);

	infomation.Hospital = cscImport("Hospitals", ScenarioFile, Num_of_Hospitals);
	infomation.POW = cscImport("Places of Worship", ScenarioFile, Num_of_POWs);
	infomation.Restuarant = cscImport("Restuarants", ScenarioFile, Num_of_Restuarants);
	infomation.Cinema = cscImport("Cinemas", ScenarioFile, Num_of_Cinemas);
	infomation.Shopping_center = cscImport("Shopping centers", ScenarioFile, Num_of_Shopping_Centers);
	infomation.Park = cscImport("Parks", ScenarioFile, Num_of_Parks);

	Matrix<int> Busnet(Num_Bus_Stops, Num_Bus_Stops);
	infomation.BusNet = TransportNetImport("Bus_stop", "Bus_Network_adjacency_matrix", ScenarioFile, Num_Bus_Stops, Busnet);

	Matrix<int> Trainnet(Num_Train_stations, Num_Train_stations);
	infomation.TrainNet = TransportNetImport("Train_station", "Train_Network_adjacency_matrix", ScenarioFile, Num_Train_stations, Trainnet);

	Matrix<int> Metronet(Num_metro_stations, Num_metro_stations);
	infomation.MetroNet = TransportNetImport("Metro_station", "Metro_Network_adjacency_matrix", ScenarioFile, Num_metro_stations, Metronet);

	infomation.Airport = AirportImport("Airport", ScenarioFile, Num_airports);

	unsigned int int_check = 0;
	double double_check = 0;

	population = SingleVar("Size_of_Population", ScenarioFile, population);
	
	std::vector<unsigned int> Pop_Pyramid = Chunked_Data("Population_Pyramind_(%)", ScenarioFile, 5, int_check);
	Population.zero_to_four = Pop_Pyramid[0];
	Population.five_to_seventeen = Pop_Pyramid[1];
	Population.eighteen_to_fourty_nine = Pop_Pyramid[2];
	Population.fifty_to_sixty_four = Pop_Pyramid[3];
	Population.sixty_five_plus = Pop_Pyramid[4];

	std::vector<unsigned int> Race_data = Chunked_Data("Population_race_data (%)", ScenarioFile, 4, int_check);
	race_data.white = Race_data[0];
	race_data.black = Race_data[1];
	race_data.hispanic = Race_data[2];
	race_data.other = Race_data[3];

	std::vector<double> child_medical = Chunked_Data("Child_medical_data (%)", ScenarioFile, 13, double_check);
	child.Asthma = child_medical[0]; 
	child.Auto_immune_disease = child_medical[1];
	child.Cardiovascular_disease = child_medical[2];
	child.chronic_lung_disease = child_medical[3];
	child.Gastrointestinal_liver_disease = child_medical[4];
	child.Hypertension = child_medical[5];
	child.Immune_disease = child_medical[6];
	child.Metabolic_disease = child_medical[7];
	child.Neurological_disease = child_medical[8];
	child.Obesity = child_medical[9];
	child.Renal_disease = child_medical[10];
	child.other_disease = child_medical[11];
	child.no_known_disease = child_medical[12];

	std::vector<double> adult_medical = Chunked_Data("Adult_medical_data (%)", ScenarioFile, 13, double_check);
	adult.Asthma = adult_medical[0];
	adult.Auto_immune_disease = adult_medical[1];
	adult.Cardiovascular_disease = adult_medical[2];
	adult.chronic_lung_disease = adult_medical[3];
	adult.Gastrointestinal_liver_disease = adult_medical[4];
	adult.Hypertension = adult_medical[5];
	adult.Immune_disease = adult_medical[6];
	adult.Metabolic_disease = adult_medical[7];
	adult.Neurological_disease = adult_medical[8];
	adult.Obesity = adult_medical[9];
	adult.Renal_disease = adult_medical[10];
	adult.other_disease = adult_medical[11];
	adult.no_known_disease = adult_medical[12];

	std::vector<unsigned int> output = Chunked_Data("Output_Data", ScenarioFile, 9, int_check);
	param.count = output[0];
	param.R0 = output[1];
	param.Suceptable = output[2];
	param.Infected = output[3];
	param.Recovered = output[4];
	param.Hostipilized = output[5];
	param.Dead = output[6];
	param.mortality_rate = output[7];
	param.morbidity_rate = output[8];

	std::vector<double> poll = Chunked_Data("Social_Distance_policies", ScenarioFile, 7, double_check);
	policies.L1 = poll[0];
	policies.L2 = poll[1];
	policies.L3 = poll[2];
	policies.L4 = poll[3];
	policies.L5 = poll[4];
	policies.L6 = poll[5];
	policies.L7 = poll[6];

	if (errors != 0)
	{
		std::cout << "File read incorrectly" << std::endl;
		Log error(Log::LogLevelCriticalError);
		error.LogFucntion(Log::LogLevelCriticalError, 4);
		return 0;
	}
	else
	{
		std::cout << "File read correctly" << std::endl;
		Log success(Log::LogLevelInfo);
		success.LogFucntion(Log::LogLevelInfo, 3);
		return 1;
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
		csc(ScenarioFile, "Primary Schools", Num_of_Primary_Schools);
		csc(ScenarioFile, "Secondry Schools", Num_of_Secondry_Schools);
		csc(ScenarioFile, "Further Education", Num_of_Uni);
		
		ScenarioFile << std::endl << "Public_Services" << std::endl;
		csc(ScenarioFile, "Hospitals", Num_of_Hospitals);
		csc(ScenarioFile, "Places of Worship", Num_of_POWs);
		csc(ScenarioFile, "Restuarants", Num_of_Restuarants);
		csc(ScenarioFile, "Cinemas", Num_of_Cinemas);
		csc(ScenarioFile, "Shopping centers", Num_of_Shopping_Centers);
		csc(ScenarioFile, "Parks", Num_of_Parks);

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

				ScenarioFile << "Bus_stop " << (i + 1) << std::endl;
				ScenarioFile << "Type" << std::endl;
				while (NotCorrectInput)
				{
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

				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				std::pair<int, std::pair<int, int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				//std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_Bus_Stops, Num_Bus_Stops);
			std::cout << "Adjaceny matrix to represent the bus network." << std::endl;
			ScenarioFile << "Bus_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_Bus_Stops; i++)
			{
				std::cout << "Bus stop " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << " Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_Bus_Stops; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To Bus stop " << (a + 1) << " at location: " << Transport[a].second.first << " , " << Transport[a].second.second << " Tile number: " << Transport[a].first << std::endl << "If so how many counts does it take, if not put 0: ";
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

				ScenarioFile << "Train_station " << (i + 1) << std::endl;
				ScenarioFile << "Type" << std::endl;
				while (NotCorrectInput)
				{
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

				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				std::pair<int, std::pair<int , int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				//std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_Train_stations, Num_Train_stations);
			std::cout << "Adjaceny matrix to represent the train network." << std::endl;
			ScenarioFile << "Train_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_Train_stations; i++)
			{
				std::cout << "Train station " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << " Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_Train_stations; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To train station " << (a + 1) << " at location: " << Transport[a].second.first << " , " << Transport[a].second.second << " Tile number: " << Transport[a].first << std::endl << "If so how many counts does it take, if not put 0: ";
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

				ScenarioFile << "Airport " << (i + 1) << std::endl;

				int x, y, tile_num = 0;

				std::cout << "X coord of the Airport (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the Airport (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;
				std::cout << "Number of staff: ";
				std::cin >> staff;

				ScenarioFile << x << std::endl << y << std::endl << tile_num << std::endl << staff << std::endl << std::endl;

				//std::system("CLS");
			}
		}

		Transport.clear();

		{
			ScenarioFile << std::endl << "Metro Network" << std::endl;
			ScenarioFile << "Number of Metro stations" << std::endl;

			std::cout << "Number of Metro stations: ";
			std::cin >> Num_metro_stations;
			ScenarioFile << Num_metro_stations << std::endl;

			for (unsigned int i = 0; i < Num_metro_stations; i++)
			{
				int x, y, tile_num = 0;

				std::cout << "X coord of the Metro station (0 being the bottom left corner): ";
				std::cin >> x;
				std::cout << "Y coord of the Metro station (0 being the bottom left corner): ";
				std::cin >> y;
				std::cout << "What tile is the on: ";
				std::cin >> tile_num;

				ScenarioFile << "Metro_station " << (i + 1) << std::endl;
				ScenarioFile << "Type" << std::endl << "0" << std::endl << x << std::endl << y << std::endl << tile_num << std::endl << "0" << std::endl << std::endl;

				std::pair<int, std::pair<int, int>> loc;
				loc.first = tile_num;
				loc.second.first = x;
				loc.second.second = y;
				Transport.insert(std::make_pair(i, loc));

				//std::system("CLS");
			}

			Matrix<int>* Adjacency = new Matrix<int>(Num_metro_stations, Num_metro_stations);
			std::cout << "Adjaceny matrix to represent the Metro network." << std::endl;
			ScenarioFile << "Metro_Network_adjacency_matrix" << std::endl;
			for (unsigned int i = 0; i < Num_metro_stations; i++)
			{
				std::cout << "Metro station " << (i + 1) << " Location: " << Transport[i].second.first << " , " << Transport[i].second.second << " Tile number: " << Transport[i].first << std::endl;
				for (unsigned int a = 0; a < Num_metro_stations; a++)
				{
					if (a != i)
					{
						unsigned int time;
						std::cout << "To Metro station " << (a + 1) << " at location: " << Transport[a].second.first << " , " << Transport[a].second.second << " Tile number: " << Transport[a].first << std::endl << "If so how many counts does it take, if not put 0: ";
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
		ScenarioFile << "Size_of_Population" << std::endl;
		std::cout << "Population: ";
		std::cin >> population;
		ScenarioFile << population << std::endl;

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
		ScenarioFile << "Adult_medical_data (%)" << std::endl;

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
		ScenarioFile << param->count << std::endl;
		
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
	std::cout << "Number of " << type << " : ";
	std::cin >> number;
	
	Scenariofile << "Num_of_" << type << std::endl;
	Scenariofile << number << std::endl << std::endl;

	for (unsigned int i = 0; i < number; i++)
	{
		int x, y = 0;
		unsigned int tile_num, capacity, staff = 0;

		std::cout << type << " " << (i+1) << std::endl;

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

		//std::system("CLS");
	}
}

std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, unsigned int>> Scenario::cscImport(std::string text, std::ifstream& Scenariofile, unsigned int& amount)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, unsigned int>> TempInput;

	for (unsigned int i = 0; i < amount; i++)
	{
		int x, y;
		unsigned int tile_num, staff, capcity;
		bool LineFound = false;

		while (getline(Scenariofile, line))
		{
			LineFound = false;
			if (line.find(text + " " + std::to_string(i + 1)) != std::string::npos)
			{
				LineFound = true;
			}
			if (LineFound)
			{ 
				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, x))
				{
					proxy >> x;
					//std::cout << x << ", ";
				}
				else
				{
					errors++;
				}
				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, y))
				{
					proxy >> y;
					//std::cout << y << std::endl;
				}
				else
				{
					errors++;
				}
				proxy.str("");
				proxy.clear();


				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, tile_num))
				{
					proxy >> tile_num;
					//std::cout << tile_num << std::endl;
				}
				else
				{
					errors++;
				}
				proxy.str("");
				proxy.clear();


				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, staff))
				{
					proxy >> staff;
					//std::cout << staff << std::endl;
				}
				else
				{
					errors++;
				}
				proxy.str("");
				proxy.clear();


				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, capcity))
				{
					proxy >> capcity;
					//std::cout << capcity << std::endl;
				}
				else
				{
					errors++;
				}
				proxy.str("");
				proxy.clear();


				std::pair<int, int> coord;
				coord.first = x;
				coord.second = y;

				std::tuple<std::pair<int, int>, unsigned int, unsigned int, unsigned int> info = { coord, tile_num, staff, capcity };

				TempInput.insert(std::make_pair(i, info));
				break;
			}
		}
		if (proxy.eof())
		{
			errors++;
			Log log(Log::LogLevelCriticalError);
			log.LogFucntion(Log::LogLevelCriticalError, 3);
		}
	}
	return TempInput;

}

std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int>> Scenario::AirportImport(std::string text, std::ifstream& Scenariofile, unsigned int& amount)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int>> Transport;

	for (unsigned int i = 0; i < amount; i++)
	{
		int x, y;
		unsigned int tile_num, staff;
		bool Linefound;

		while (getline(Scenariofile, line))
		{
			Linefound = false;
			if (line.find(text + " " + std::to_string(i + 1)) != std::string::npos)
			{
				Linefound = true;
			}
			if (Linefound)
			{
				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, x))
				{
					proxy >> x;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, y))
				{
					proxy >> y;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, tile_num))
				{
					proxy >> tile_num;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, staff))
				{
					proxy >> staff;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				std::pair<int, int> coord;
				coord.first = x;
				coord.second = y;

				std::tuple<std::pair<int, int>, unsigned int, unsigned int> info = { coord, tile_num, staff };
				Transport.insert(std::make_pair(i, info));

				break;
			}
		}
		if (proxy.eof())
		{
			errors++;
			Log log(Log::LogLevelCriticalError);
			log.LogFucntion(Log::LogLevelCriticalError, 3);
		}
	}
	return Transport;
}


std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> Scenario::TransportNetImport(std::string text, std::string adjline, std::ifstream& Scenariofile, unsigned int& amount, Matrix<int>& adjency)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> Transport;

	for (unsigned int i = 0; i < amount; i++)
	{
		int x, y, type;
		unsigned int tile_num, staff;
		bool Linefound;

		while (getline(Scenariofile, line))
		{
			Linefound = false;
			if (line.find(text + " " + std::to_string(i + 1)) != std::string::npos)
			{
				Linefound = true;
			}
			if (Linefound)
			{
				getline(Scenariofile, line);
				getline(Scenariofile, line);
				proxy << line;
				
				if (CheckType(proxy, type))
				{
					proxy >> type;
				}
				else
				{
					errors++;
				}
				
				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, x))
				{
					proxy >> x;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, y))
				{
					proxy >> y;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, tile_num))
				{
					proxy >> tile_num;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				getline(Scenariofile, line);
				proxy << line;

				if (CheckType(proxy, staff))
				{
					proxy >> staff;
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();

				adjency.GetMatrix(Scenariofile, adjline, amount);

				std::pair<int, int> coord;
				coord.first = x;
				coord.second = y;

				std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>> info = { coord, tile_num, staff, type, adjency };
				Transport.insert(std::make_pair(i, info));

				break;
			}
		}
		if (proxy.eof())
		{
			errors++;
			Log log(Log::LogLevelCriticalError);
			log.LogFucntion(Log::LogLevelCriticalError, 3);
		}
	}
	return Transport;
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

int Scenario::SingleVar(std::string text, std::ifstream &Scenariofile, unsigned int &value)
{
	
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;

	bool LineFound = false;
	while (getline(Scenariofile, line))
	{
		if (LineFound)
		{
			proxy << line;
			if (CheckType(proxy, value))
			{
				proxy >> value;
				return value;
			}
			break;
		}
		if (line.find(text) != std::string::npos)
		{
			LineFound = true;
		}
	}

	errors++;
	Log SingleV(Log::LogLevelCriticalError);
	SingleV.LogFucntion(Log::LogLevelCriticalError, 2);

	return NULL;
}
double Scenario::SingleVar(std::string text, std::ifstream& Scenariofile, double &value)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;

	bool LineFound = false;
	while (getline(Scenariofile, line))
	{
		if (LineFound)
		{
			proxy << line;
			if (CheckType(proxy, value))
			{
				proxy >> value;
				return value;
			}
			break;
		}
		if (line.find(text) != std::string::npos)
		{
			LineFound = true;
		}
	}

	errors++;
	Log SingleV(Log::LogLevelCriticalError);
	SingleV.LogFucntion(Log::LogLevelCriticalError, 2);

	return NULL;
}

std::vector<unsigned int> Scenario::Chunked_Data(std::string text, std::ifstream& Scenariofile, unsigned int amount, unsigned int& check_value)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;
	
	std::vector<unsigned int> return_values;

	bool Linefound = false;
	while (getline(Scenariofile, line))
	{
		if (line.find(text) != std::string::npos)
		{
			Linefound = true;
		}
		if (Linefound)
		{
			for (unsigned int i = 0; i < amount; i++)
			{
				getline(Scenariofile, line);
				
				proxy << line;
				if (CheckType(proxy, check_value))
				{
					proxy >> check_value;
					return_values.push_back(check_value);
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();
			}
			return return_values;
			break;
		}
	}

	errors++;
	Log log(Log::LogLevelCriticalError);
	log.LogFucntion(Log::LogLevelCriticalError, 3);
	
	return return_values;
}

std::vector<double> Scenario::Chunked_Data(std::string text, std::ifstream& Scenariofile, unsigned int amount, double& check_value)
{
	Scenariofile.clear();
	Scenariofile.seekg(0, std::ios::beg);
	std::string line;
	std::stringstream proxy;

	std::vector<double> return_values;

	bool Linefound = false;
	while (getline(Scenariofile, line))
	{
		if (line.find(text) != std::string::npos)
		{
			Linefound = true;
		}
		if (Linefound)
		{
			for (unsigned int i = 0; i < amount; i++)
			{
				getline(Scenariofile, line);

				proxy << line;
				if (CheckType(proxy, check_value))
				{
					proxy >> check_value;
					return_values.push_back(check_value);
				}
				else
				{
					errors++;
				}

				proxy.str("");
				proxy.clear();
			}
			return return_values;
			break;
		}
	}

	errors++;
	Log log(Log::LogLevelCriticalError);
	log.LogFucntion(Log::LogLevelCriticalError, 3);

	return return_values;
}

template <typename T>
bool Scenario::CheckType(std::stringstream& input, T& check)
{
	input >> check;
	if (input.fail())
	{
		Log InputError(Log::LogLevelError);
		InputError.LogFucntion(Log::LogLevelCriticalError, 2);
		return false;
	}
	else
	{
		return true;
	}
}

void Scenario::ScenarioCreate()
{
	//This could be a feature, probably write after the main model. 
}

void Scenario::CreateModel(Tile tile[], World_Infomation& infomation_values, Population_Pyramid& Population_data, Population_race_data& race_data_values , Medical_data& child_medical_data, Medical_data& adult_medical_data, Scenario_Parameters& param, Social_Distance_poll& policy, Actor population_list[], unsigned int& Actor_size, Education_Buildings primary_school[], unsigned int& primary_size, Education_Buildings secondary_school[], unsigned int& secondary_size, Education_Buildings further_education[], unsigned int& further_size, Public_Buildings hosptial[], unsigned int& hospital_size, Public_Buildings place_of_worship[], unsigned int& pow_size, Public_Buildings Restaurant[], unsigned int& restaurant_size, Public_Buildings Cinema[], unsigned int& cinema_size, Public_Buildings shopping_center[], unsigned int& center_size, Public_Buildings parks[], unsigned int& park_size, Public_transport_building BusNet[], unsigned int& BusNet_size, Public_transport_building TrainNet[], unsigned int& TrainNet_size, Public_transport_building Air[], unsigned int& Air_size, Public_transport_building MetroNet[], unsigned int& MetroNet_size, Transport_Net& transport_network)
{
	Log createmodellog(Log::LogLevelInfo);
	unsigned int errors = 0;

	//could probably write this as a function but cba to do at the moment.

	unsigned int i = 0;
	for (auto elem : infomation_values.Primary_school)
	{
		if (i == primary_size && primary_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;

		}

		primary_school[i].set_type(Education_Buildings::Primary_school);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		primary_school[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		primary_school[i].set_staff(staff);
		primary_school[i].set_capacity(capacity);

		tile[tile_number - 1].edu_buildings.push_back(&primary_school[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Secondry_school)
	{
		if (i == secondary_size && secondary_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		secondary_school[i].set_type(Education_Buildings::Secondary_school);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		secondary_school[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		secondary_school[i].set_staff(staff);
		secondary_school[i].set_capacity(capacity);

		tile[tile_number - 1].edu_buildings.push_back(&secondary_school[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.University)
	{
		if (i == further_size && further_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		further_education[i].set_type(Education_Buildings::University);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		further_education[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		further_education[i].set_staff(staff);
		further_education[i].set_capacity(capacity);
		
		tile[tile_number - 1].edu_buildings.push_back(&further_education[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Hospital)
	{
		if (i == hospital_size && hospital_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		hosptial[i].set_type(Public_Buildings::Hospital);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		hosptial[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		hosptial[i].set_staff(staff);
		hosptial[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&hosptial[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.POW)
	{
		if (i == pow_size && pow_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		place_of_worship[i].set_type(Public_Buildings::Place_of_worship);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		place_of_worship[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		place_of_worship[i].set_staff(staff);
		place_of_worship[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&hosptial[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Restuarant)
	{
		if (i == restaurant_size && restaurant_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		Restaurant[i].set_type(Public_Buildings::restuarant);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		Restaurant[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		Restaurant[i].set_staff(staff);
		Restaurant[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&Restaurant[i]);
		i++;
	}

	i = 0;
	
	for (auto elem : infomation_values.Cinema)
	{
		if (i == cinema_size && cinema_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}
		Cinema[i].set_type(Public_Buildings::cinema);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		Cinema[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		Cinema[i].set_staff(staff);
		Cinema[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&Cinema[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Shopping_center)
	{
		if (i == center_size && center_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}
		shopping_center[i].set_type(Public_Buildings::shopping_center);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		shopping_center[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		shopping_center[i].set_staff(staff);
		shopping_center[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&shopping_center[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Park)
	{
		if (i == park_size && park_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}
		parks[i].set_type(Public_Buildings::parks);
		auto [x_and_y, tile_number, staff, capacity] = elem.second;
		parks[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		parks[i].set_staff(staff);
		parks[i].set_capacity(capacity);

		tile[tile_number - 1].Pub_buildings.push_back(&shopping_center[i]);
		i++;
	}

	for (auto elem : infomation_values.BusNet)
	{
		if (i == BusNet_size && BusNet_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		BusNet[i].set_type(Public_transport_building::Bus);
		auto [x_and_y, tile_number, staff, style, transport_matrix ] = elem.second;
		BusNet[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		BusNet[i].set_style(style);
		BusNet[i].set_staff(staff);

		transport_network.Bus_Network.push_back(&BusNet[i]);
		if (i+1 == BusNet_size)
		{
			transport_network.BusNetwork->MatrixResize(transport_matrix.Get_num_row(), transport_matrix.Get_num_col());

			for (int a = 0; a < transport_matrix.Get_num_row(); a++)
			{
				std::vector<int> row = transport_matrix.GetRow(a+1);

				for (int e = 0; e < transport_matrix.Get_num_col(); e++)
				{
					transport_network.BusNetwork->MatrixEdit(a+1, e+1, row[e]);
				}
			}
		}

		tile[tile_number - 1].public_transport.push_back(&BusNet[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.TrainNet)
	{
		if (i == TrainNet_size && TrainNet_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		TrainNet[i].set_type(Public_transport_building::Train);
		auto [x_and_y, tile_number, staff, style, transport_matrix] = elem.second;
		TrainNet[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		TrainNet[i].set_style(style);
		TrainNet[i].set_staff(staff);

		transport_network.Train_Network.push_back(&TrainNet[i]);
		if (i + 1 == TrainNet_size)
		{
			transport_network.TrainNetwork->MatrixResize(transport_matrix.Get_num_row(), transport_matrix.Get_num_col());

			for (int a = 0; a < transport_matrix.Get_num_row(); a++)
			{
				std::vector<int> row = transport_matrix.GetRow(a + 1);

				for (int e = 0; e < transport_matrix.Get_num_col(); e++)
				{
					transport_network.TrainNetwork->MatrixEdit(a + 1, e + 1, row[e]);
				}
			}
		}

		tile[tile_number - 1].public_transport.push_back(&TrainNet[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.MetroNet)
	{
		if (i == MetroNet_size && MetroNet_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		MetroNet[i].set_type(Public_transport_building::Metro);
		auto [x_and_y, tile_number, staff, style, transport_matrix] = elem.second;
		MetroNet[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		MetroNet[i].set_style(style);
		MetroNet[i].set_staff(staff);

		transport_network.Metro_Network.push_back(&MetroNet[i]);
		if (i + 1 == MetroNet_size)
		{
			transport_network.MetroNetwork->MatrixResize(transport_matrix.Get_num_row(), transport_matrix.Get_num_col());

			for (int a = 0; a < transport_matrix.Get_num_row(); a++)
			{
				std::vector<int> row = transport_matrix.GetRow(a + 1);

				for (int e = 0; e < transport_matrix.Get_num_col(); e++)
				{
					transport_network.MetroNetwork->MatrixEdit(a + 1, e + 1, row[e]);
				}
			}
		}

		tile[tile_number - 1].public_transport.push_back(&MetroNet[i]);
		i++;
	}

	i = 0;

	for (auto elem : infomation_values.Airport)
	{
		if (i == Air_size && Air_size != 0)
		{
			createmodellog.LogFucntion(Log::LogLevelCriticalError, 2);
			errors++;
			break;
		}

		Air[i].set_type(Public_transport_building::Airport);
		auto [x_and_y, tile_number, staff] = elem.second;
		Air[i].set_location(x_and_y.first, x_and_y.second, tile_number);
		Air[i].set_staff(staff);

		transport_network.Airports.push_back(&Air[i]);
		tile[tile_number - 1].public_transport.push_back(&Air[i]);
		i++;
	}

	if (errors == 0)
	{
		createmodellog.LogFucntion(Log::LogLevelInfo, 4);
		std::cout << "WORLD BUILT SUCCESSFULLY" << std::endl;
	}
	else
	{
		createmodellog.LogFucntion(Log::LogLevelError, 3);
		std::cout << "WORLD BUILT WITH SOME ERRORS HOWEVER MODEL WILL STILL RUN" << std::endl;
	}

	std::vector<unsigned int> population_age_weights = { *&Population_data.zero_to_four, *&Population_data.five_to_seventeen, *&Population_data.eighteen_to_fourty_nine, *&Population_data.fifty_to_sixty_four, *&Population_data.sixty_five_plus };
	std::vector<unsigned int> population_race_weights = { *&race_data_values.white, *&race_data_values.black,*&race_data_values.hispanic,*&race_data_values.other };
	std::vector<double> population_child_medical = { *&child_medical_data.Asthma, *&child_medical_data.Auto_immune_disease, *&child_medical_data.Cardiovascular_disease, *&child_medical_data.chronic_lung_disease, *&child_medical_data.Gastrointestinal_liver_disease, *&child_medical_data.Hypertension, *&child_medical_data.Hypertension, *&child_medical_data.Immune_disease, *&child_medical_data.Metabolic_disease, *&child_medical_data.Neurological_disease, *&child_medical_data.no_known_disease, *&child_medical_data.Obesity, *&child_medical_data.other_disease, *&child_medical_data.Renal_disease };
	std::vector<double> population_adult_medical = { *&adult_medical_data.Asthma, *&adult_medical_data.Auto_immune_disease, *&adult_medical_data.Cardiovascular_disease, *&adult_medical_data.chronic_lung_disease, *&adult_medical_data.Gastrointestinal_liver_disease, *&adult_medical_data.Hypertension, *&adult_medical_data.Hypertension, *&adult_medical_data.Immune_disease, *&adult_medical_data.Metabolic_disease, *&adult_medical_data.Neurological_disease, *&adult_medical_data.no_known_disease, *&adult_medical_data.Obesity, *&adult_medical_data.other_disease, *&adult_medical_data.Renal_disease };

	std::vector<unsigned int> population_age;
	std::vector<unsigned int> population_race;
	std::vector<unsigned int> medical_child;
	std::vector<unsigned int> medical_adult;

	population_age = Random::Discrete_distribution(population_age_weights, Actor_size);
	population_race = Random::Discrete_distribution(population_race_weights, Actor_size);

	unsigned int num_of_children = 0;
	for (auto value : population_age)
	{
		if (value == 0 || value == 1 )
		{
			num_of_children++;
		}
	}

	medical_child = Random::Discrete_distribution(population_child_medical, num_of_children);
	medical_adult = Random::Discrete_distribution(population_adult_medical, (Actor_size - num_of_children));

	for (unsigned int i = 0; i < Actor_size; i++)
	{
		/*DO risk calculations*/
		switch (population_age[i])
		{
		case 0:
			population_list[i].Age(Actor::zero_to_four);
			break;
		case 1:
			population_list[i].Age(Actor::five_to_seventeen);
			break;
		case 2:
			population_list[i].Age(Actor::eighteen_to_fortynine);
			break;
		case 3:
			population_list[i].Age(Actor::fifty_to_sixtyfour);
			break;
		case 4:
			population_list[i].Age(Actor::sixtyfive_plus);
			break;
		default:
			break;
		}
	}

	std::cin.get();
	

	std::cin.get();
	
}





