#pragma once

#include "Scenario.h"
#include "Setup_info.h"
#include "Objects.h"
//#include "Director.h"

#include <cstdlib>
#include <algorithm>

#include "Random.h"

namespace Model
{
	void RunModel();
	//void RunModel(); The overload
	void CreateModel();
	void RunRandomModel();
	
	/*INFECTION_CHECKS*/
	void Infection_check_outside(std::vector<Actor*>& sucept, std::vector<Actor*>& infected);
	
	std::string Get_filename();

}

namespace functions
{
	std::vector<std::pair<int, int>> generate_circle(unsigned int radius, std::pair<int, int> center);
}

struct Model_Data
{
	unsigned int counts = 0;

	//SIRHD
	std::vector<Actor*> sucept;
	std::vector<Actor*> infected;
	std::vector<Actor*> recovered;
	std::vector<Actor*> hostipilized;
	std::vector<Actor*> dead;

	//POLICIES
	double L1;
	double L2;
	double L3;
	double L4;
	double L5;
	double L6;
	double L7;

	//OUTPUT DATA
	int R0;
	int Sucept;
	int Infected;
	int Rec;
	int Host;
	int Dead;
	int mortality;
	int morbidity;
};