#include "Model.h"

void Model::CreateModel()
{
	Scenario CreateModel;
	CreateModel.ScenarioEditor();
}

void Model::RunModel()
{
	Scenario RunModel(Get_filename());
	World_Infomation Infomation;
	Scenario::Population_Pyramid Population_spread;
	Scenario::Population_race_data Population_diversity;
	Scenario::Medical_data child_medical;
	Scenario::Medical_data adult_medical;
	Scenario::Scenario_Parameters scenario_param;
	Scenario::Social_Distance_poll policies;

	if (RunModel.ScenarioImport(Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies) == true)
	{
		// Make array's
		Actor* actor = new Actor[RunModel.population];
		Tile* tiles = new Tile[RunModel.Num_Of_Tiles];
		Education_Buildings* primary_school = new Education_Buildings[RunModel.Num_of_Primary_Schools];
		Education_Buildings* secondry_school = new Education_Buildings[RunModel.Num_of_Secondry_Schools];
		Education_Buildings* further_education = new Education_Buildings[RunModel.Num_of_Uni];

		Public_Buildings* Hospital = new Public_Buildings[RunModel.Num_of_Hospitals];
		Public_Buildings* POW = new Public_Buildings[RunModel.Num_of_POWs];
		Public_Buildings* Restuarant = new Public_Buildings[RunModel.Num_of_Restuarants];
		Public_Buildings* Cinema = new Public_Buildings[RunModel.Num_of_Cinemas];
		Public_Buildings* Shopping_center = new Public_Buildings[RunModel.Num_of_Shopping_Centers];
		Public_Buildings* Parks = new Public_Buildings[RunModel.Num_of_Parks];

		Public_transport_building* Bus = new Public_transport_building[RunModel.Num_Bus_Stops];
		Public_transport_building* Train = new Public_transport_building[RunModel.Num_Train_stations];
		Public_transport_building* Airport = new Public_transport_building[RunModel.Num_airports];
		Public_transport_building* Metro = new Public_transport_building[RunModel.Num_metro_stations];

		Transport_Net* transport = new Transport_Net;

		std::vector<std::vector<Actor*>> family_groups = {};
		std::vector<House*> houses = {};
		std::vector<Generic_work*> work_places = {};

		RunModel.CreateModel(tiles, Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies, actor, RunModel.population, primary_school, RunModel.Num_of_Primary_Schools, secondry_school, RunModel.Num_of_Secondry_Schools, further_education, RunModel.Num_of_Uni, Hospital, RunModel.Num_of_Hospitals, POW, RunModel.Num_of_POWs, Restuarant, RunModel.Num_of_Restuarants, Cinema, RunModel.Num_of_Cinemas, Shopping_center, RunModel.Num_of_Shopping_Centers, Parks, RunModel.Num_of_Parks, Bus, RunModel.Num_Bus_Stops, Train, RunModel.Num_Train_stations, Airport, RunModel.Num_airports, Metro, RunModel.Num_metro_stations, *transport, family_groups, houses, work_places);
		
		Model_Data model_data;

		model_data.counts = scenario_param.count;
		
		model_data.L1 = policies.L1;
		model_data.L2 = policies.L2;
		model_data.L3 = policies.L3;
		model_data.L4 = policies.L4;
		model_data.L5 = policies.L5;
		model_data.L6 = policies.L6;
		model_data.L7 = policies.L7;

		model_data.R0 = scenario_param.R0;
		model_data.Sucept = scenario_param.Suceptable;
		model_data.Infected = scenario_param.Infected;
		model_data.Rec = scenario_param.Recovered;
		model_data.Host = scenario_param.Hostipilized;
		model_data.Dead = scenario_param.Dead;
		model_data.mortality = scenario_param.mortality_rate;
		model_data.morbidity = scenario_param.morbidity_rate;

		for (int i = 0; i < RunModel.population; i++)
		{
			model_data.sucept.push_back(&actor[i]);
			model_data.sucept[i]->set_stage(Actor::sucept);
		}

		for (uint32_t i = 0; i < get_starting_infected(); i++)
		{
			int x = Random::random_number(0, model_data.sucept.size(), {});
			model_data.infected.push_back(model_data.sucept[x]);
			model_data.infected[i]->set_stage(Actor::infect);
			model_data.sucept.erase(model_data.sucept.begin() + x);
		}

		// Test code
		Infection_check_outside(model_data.sucept, model_data.infected); 
		//actor[0].weighted_walk(std::make_pair(9, 7));
		//std::cout << "destination reached" << std::endl;
	}
	std::cin.get();
}

void Model::RunRandomModel()
{
	
}


void Model::Infection_check_outside(std::vector<Actor*>& sucept, std::vector<Actor*>& infected)
{
	for (int i = 0; i < infected.size(); i++)
	{
		if (infected[i]->get_location() != Actor::outside)
		{
			break;
		}
		auto [x, y, tile] = infected[i]->Get_Location();
		std::vector<std::pair<int, int>> infection_circle = functions::generate_circle(get_infection_distance(), std::make_pair(x, y));
		int removed = 0;
		for (int a = 0; a < sucept.size(); a++)
		{
			auto [x1, y1, tile_num] = sucept[a]->Get_Location();
			if (tile_num == tile && sucept[a]->get_location() == Actor::outside && sucept[a]->state_check() == Actor::sucept);
			{
				std::pair<int, int> location = { x1, y1 };
				if (std::find(infection_circle.begin(), infection_circle.end(), location) != infection_circle.end())
				{
					bool infection = false;
					double infection_chance = calculations::infection_prob(sucept[a]->get_host_risk(), infected[i]->get_infectivity_risk());
					
					std::vector<double> weight_vector = { infection_chance, (1 - infection_chance) };
					if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
					{
						sucept[a]->set_stage(Actor::infect);
						infected.push_back(sucept[a]);
						sucept.erase(sucept.begin() + a - removed);
						removed++;
					}
				}
			}
		}
	}
}

std::string Model::Get_filename()
{
	std::string filename;

	std::cout << "Scenario filename: ";
	std::cin >> filename;
	return filename;
}

std::vector<std::pair<int, int>> functions::generate_circle(unsigned int radius, std::pair<int, int> center)
{
	std::vector <std::pair<int, int>> points;
	points.push_back(center);

	int x = 0;
	int y = radius;
	bool loop_complete = false;
	bool x_positive = true;
	bool y_positive = false;
	bool first_loop = true;

	std::pair<int, int> start = { center.first, center.second + radius };
	std::pair<int, int> current_location;
	while (loop_complete == false)
	{
		if (y >= 0)
		{
			if (x >= 0)
			{
				for (int i = 0; i < radius - x + 1; i++)
				{
					points.push_back(std::make_pair((center.second + radius - y), (center.first + radius - x - i)));
				}
				current_location.first = center.second + radius - y;
				current_location.second = center.first + radius - x;
			}
			else
			{
				for (int i = 0; i < radius + x + 1; i++)
				{
					points.push_back(std::make_pair((center.second - radius + y), (center.first + radius + x - i)));
				}
				current_location.first = center.second - radius + y;
				current_location.second = center.first + radius + x;
			}
		}
		else
		{
			if (x >= 0)
			{
				for (int i = 0; i < radius - x + 1; i++)
				{
					
					points.push_back(std::make_pair((center.second + radius + y), (center.first - radius + x + i)));
					
				}
				current_location.first = center.second + radius + y;
				current_location.second = center.first - radius + x;
			}
			else
			{
				for (int i = 0; i < radius + x + 1; i++)
				{
					
					points.push_back(std::make_pair((center.second - radius - y), (center.first - radius - x + i)));
					
				}
				current_location.first = center.second - radius - y;
				current_location.second = center.first - radius - x;
			}
		}

		if (x == radius)
		{
			x_positive = false;
		}
		if (-x == radius)
		{
			x_positive = true;
		}
		if (abs(y) == radius && first_loop != true)
		{
			y_positive = true;
		}

		if (x_positive == true)
		{
			x++;
		}
		else
		{
			x--;
		}

		if (y_positive == true)
		{
			y++;
		}
		else
		{
			y--;
		}

		if (current_location == start && first_loop == false)
		{
			loop_complete = true;
		}
		first_loop = false;

	}

	return points;
}