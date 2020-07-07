#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include <string>

#include "Logging API.h"

class Scenario
{
private:
	unsigned int m_mode;
	std::string m_filepath = "Scenarios/";
public:
	// Scenario peramters will go here 

public:
	Scenario(const std::string &filename, unsigned int mode);
	Scenario(unsigned int mode);
	~Scenario();

	void ScenarioImport(); //Imports a scenario
	void ScenarioEditor(); //Allows you to create a scenario
	void ScenarioCreate(); //Generates Scenario
	void CreateModel();
};