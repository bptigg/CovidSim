#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdlib.h>
#include <utility>

#include <string>
#include <map>
#include "Matrix.h"

#include "Setup_info.h"
#include "Random.h"

#include "Buildings.h"
#include "Public_Transport_Network.h"

#include "Logging API.h"

class Scenario
{
private:
	std::string m_filepath = "Scenarios/";
	std::map<unsigned int, std::pair<int, std::pair<int, int>>> Transport; 

	int errors = 0;

public:

	/*Unique Buildinggs*/
	unsigned int tile_size;
	unsigned int Num_Of_Tiles;
	unsigned int Num_Uq_Buildings;
	unsigned int Num_of_Primary_Schools;
	unsigned int Num_of_Secondry_Schools;
	unsigned int Num_of_Uni;
	unsigned int Num_of_Hospitals;
	unsigned int Num_of_POWs;
	unsigned int Num_of_Restuarants;
	unsigned int Num_of_Cinemas;
	unsigned int Num_of_Shopping_Centers;
	unsigned int Num_of_Parks;

	/*Public Transport*/
	unsigned int Num_Bus_Stops;//Includes bus stations
	unsigned int Num_Train_stations; //Include regional stations
	unsigned int Num_airports;
	unsigned int Num_metro_stations;

	/*Population data*/
	unsigned int population;

	struct Population_Pyramid
	{
		unsigned int zero_to_four;
		unsigned int five_to_seventeen;
		unsigned int eighteen_to_fourty_nine;
		unsigned int fifty_to_sixty_four;
		unsigned int sixty_five_plus;
	};

	struct Population_race_data
	{
		unsigned int white;
		unsigned int black;
		unsigned int hispanic;
		unsigned int other;
	};

	struct Medical_data
	{
		double Asthma;
		double Auto_immune_disease;
		double Cardiovascular_disease;
		double chronic_lung_disease;
		double Gastrointestinal_liver_disease;
		double Hypertension;
		double Immune_disease;
		double Metabolic_disease;
		double Neurological_disease;
		double Obesity;
		double Renal_disease;
		double other_disease;
		double no_known_disease;
	};

	struct Scenario_Parameters
	{
		unsigned int count;

		/*Data to output*/
		unsigned int R0;
		unsigned int Suceptable;
		unsigned int Infected;
		unsigned int Recovered;
		unsigned int Hostipilized;
		unsigned int Dead;
		unsigned int mortality_rate;
		unsigned int morbidity_rate;
	};

	struct Social_Distance_poll
	{
		double L1;
		double L2;
		double L3;
		double L4;
		double L5;
		double L6;
		double L7;
	};

private:
	void csc(std::ofstream &Scenariofile, const std::string type, unsigned int number); //Coord, staff, Capacity
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> cscImport(std::string text, std::ifstream& Scenariofile, unsigned int& amount);
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> TransportNetImport(std::string text, std::string adjline, std::ifstream& Scenariofile, unsigned int& amount, Matrix<int>& adjency);
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int>> AirportImport(std::string text, std::ifstream& Scenariofile, unsigned int& amount);
	
	std::vector<unsigned int> Chunked_Data(std::string text, std::ifstream& Scenariofile, unsigned int amount, unsigned int& check_value);
	std::vector<double> Chunked_Data(std::string, std::ifstream& Scenariofile, unsigned int amount, double& check_value);
	int Input(std::string param);
	
	int SingleVar(std::string line, std::ifstream& Scenariofile, unsigned int &value);
	double SingleVar(std::string line, std::ifstream& Scenariofile, double &value);
	template<typename T>

	bool CheckType(std::stringstream& input, T& check);


public:
	Scenario(const std::string &filename);
	Scenario();
	~Scenario();

	void ScenarioImport(World_Infomation& infomation, Population_Pyramid& Population, Population_race_data& race_data, Medical_data& child, Medical_data& adult, Scenario_Parameters& param, Social_Distance_poll& policies); //Imports a scenario
	void ScenarioEditor(); //Allows you to create a scenario
	void ScenarioCreate(); //Generates Scenario
	
	void CreateModel(World_Infomation& infomation_values, Population_Pyramid& Population_data, Population_race_data& race_data_values, Medical_data& child_medical_data, Medical_data& adult_medical_data, Scenario_Parameters& param, Social_Distance_poll& policy, Actor population_list[], unsigned int& Actor_size, Education_Buildings primary_school[], unsigned int& primary_size, Education_Buildings secondary_school[], unsigned int& secondary_size, Education_Buildings further_education[], unsigned int& further_size, Public_Buildings hosptial[], unsigned int& hospital_size, Public_Buildings place_of_worship[], unsigned int& pow_size, Public_Buildings Restaurant[], unsigned int& restaurant_size, Public_Buildings Cinema[], unsigned int& cinema_size, Public_Buildings shopping_center[], unsigned int& center_size, Public_Buildings parks[], unsigned int& park_size, Public_transport_building BusNet[], unsigned int& BusNet_size, Public_transport_building TrainNet[], unsigned int& TrainNet_size, Public_transport_building Air[], unsigned int& Air_size, Public_transport_building MetroNet[], unsigned int& MetroNet_size);
	
};