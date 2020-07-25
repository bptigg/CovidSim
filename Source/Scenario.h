#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>

#include <string>


#include "Logging API.h"

class Scenario
{
private:
	std::string m_filepath = "Scenarios/";
public:
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

private:
	void csc(std::ofstream &Scenariofile, const std::string type, unsigned int number); //Coord, staff, Capacity

public:
	Scenario(const std::string &filename);
	Scenario();
	~Scenario();

	void ScenarioImport(); //Imports a scenario
	void ScenarioEditor(); //Allows you to create a scenario
	void ScenarioCreate(); //Generates Scenario
	void CreateModel();
};