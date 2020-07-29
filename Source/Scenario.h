#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>

#include <string>
#include <map>
#include "Matrix.h"


#include "Logging API.h"

class Scenario
{
private:
	std::string m_filepath = "Scenarios/";
	std::map<unsigned int, std::pair<int, std::pair<int, int>>> Transport; 

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
		std::string Output_file_name;

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
	int Input(std::string param);
	double Inputp(std::string param);

public:
	Scenario(const std::string &filename);
	Scenario();
	~Scenario();

	void ScenarioImport(); //Imports a scenario
	void ScenarioEditor(); //Allows you to create a scenario
	void ScenarioCreate(); //Generates Scenario
	void CreateModel();

};