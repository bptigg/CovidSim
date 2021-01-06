#pragma once

#include "Scenario.h"
#include "Setup_info.h"
#include "Objects.h"
#include "Director.h"

#include <cstdlib>
#include <algorithm>
#include <Windows.h>


#include "Random.h"

struct Model_Data
{
	unsigned int counts = 0;
	std::string m_filepath = "Output/";

	//SIRHD
	std::vector<Actor*> sucept;
	std::vector<Actor*> infected;
	std::vector<Actor*> recovered;
	std::vector<Actor*> hostipilized;
	std::vector<Actor*> dead;

	int total = 0;

	int previous_infected = 0;
	int now_infected = 0;

	int previous_dead = 0;
	int now_dead = 0;

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


	~Model_Data()
	{
		sucept.clear();
		infected.clear();
		recovered.clear();
		hostipilized.clear();
		dead.clear();
	}
};

namespace functions
{
	std::vector<std::pair<int, int>> generate_circle(unsigned int radius, std::pair<int, int> center);
	bool find_in_vec(const std::vector<Actor*>& vector, int& position, const Actor* value);
	void write_to_file(const Model_Data& data, std::string filename);
	bool sortbysec (const std::pair<Actor*, int>& a, const std::pair<Actor*, int>& b);
	bool remove_from_building(Actor* agent, std::vector<Tile*> tile_vec);
}

namespace Model
{
	void RunModel();
	//void RunModel(); The overload
	void CreateModel();
	void RunRandomModel();
	
	/*INFECTION_CHECKS*/
	void Infection_check_outside(std::vector<Actor*>& sucept, std::vector<Actor*>& infected, std::vector<std::pair<Actor*, int>>& return_vector);
	void transport_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_transport_building*>& building, std::vector<std::pair<Actor*, int>>& return_vector);
	void education_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Education_Buildings*>& building, std::vector<std::pair<Actor*, int>>& return_vector);
	void work_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Generic_work*>& building, std::vector<std::pair<Actor*, int>>& return_vector);
	void home_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<House*>& building, std::vector<std::pair<Actor*, int>>& return_vector);
	void building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_Buildings*>& building, std::vector<std::pair<Actor*, int>>& return_vector);
	void hospital_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_Buildings*>& Hospital, std::vector<std::pair<Actor*, int>>& return_vector);
	void transport_infection(std::vector<Actor*>& succept, std::vector<Actor*>& infected, std::vector<std::pair<Actor*, int>>& return_vector);
	
	std::string Get_filename(std::string& file_name);

	void get_agent(const std::vector<Actor*> agents, const bool& leave);
	void check_escape(bool& escape, const bool& model_end);

}

