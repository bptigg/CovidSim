#include "Model.h"

void Model::CreateModel()
{
	Scenario CreateModel;
	CreateModel.ScenarioEditor();
}

void Model::RunModel()
{
	std::string filename;
	Scenario RunModel(Get_filename(filename));
	World_Infomation Infomation;
	Scenario::Population_Pyramid Population_spread;
	Scenario::Population_race_data Population_diversity;
	Scenario::Medical_data child_medical;
	Scenario::Medical_data adult_medical;
	Scenario::Scenario_Parameters scenario_param;
	Scenario::Social_Distance_poll policies;

	Log model_log(Log::LogLevelInfo);

	if (RunModel.ScenarioImport(Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies) == true)
	{

		std::vector<Education_Buildings*> schools_vec;
		std::vector<Public_Buildings*> hospital_vec;
		std::vector<Public_Buildings*> public_buildings_vec;
		std::vector<Public_transport_building*> transport_buildings_vec;

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
		
		std::vector<Tile*> tiles_vec = {};
		std::vector<Actor*> actor_vec = {};

		RunModel.CreateModel(tiles, Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies, actor, RunModel.population, primary_school, RunModel.Num_of_Primary_Schools, secondry_school, RunModel.Num_of_Secondry_Schools, further_education, RunModel.Num_of_Uni, Hospital, RunModel.Num_of_Hospitals, POW, RunModel.Num_of_POWs, Restuarant, RunModel.Num_of_Restuarants, Cinema, RunModel.Num_of_Cinemas, Shopping_center, RunModel.Num_of_Shopping_Centers, Parks, RunModel.Num_of_Parks, Bus, RunModel.Num_Bus_Stops, Train, RunModel.Num_Train_stations, Airport, RunModel.Num_airports, Metro, RunModel.Num_metro_stations, *transport, family_groups, houses, work_places);
		
		for (int i = 0; i < RunModel.Num_of_Primary_Schools; i++)
		{
			schools_vec.push_back(&primary_school[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Secondry_Schools; i++)
		{
			schools_vec.push_back(&secondry_school[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Uni; i++)
		{
			schools_vec.push_back(&further_education[i]);
		}

		for (int i = 0; i < RunModel.Num_of_Hospitals; i++)
		{
			hospital_vec.push_back(&Hospital[i]);
		}

		for (int i = 0; i < RunModel.Num_of_POWs; i++)
		{
			public_buildings_vec.push_back(&POW[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Restuarants; i++)
		{
			public_buildings_vec.push_back(&Restuarant[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Restuarants; i++)
		{
			public_buildings_vec.push_back(&Restuarant[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Cinemas; i++)
		{
			public_buildings_vec.push_back(&Cinema[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Shopping_Centers; i++)
		{
			public_buildings_vec.push_back(&Shopping_center[i]);
		}
		for (int i = 0; i < RunModel.Num_of_Parks; i++)
		{
			public_buildings_vec.push_back(&Parks[i]);
		}

		for (int i = 0; i < RunModel.Num_Bus_Stops; i++)
		{
			transport_buildings_vec.push_back(&Bus[i]);
		}
		for (int i = 0; i < RunModel.Num_Train_stations; i++)
		{
			transport_buildings_vec.push_back(&Train[i]);
		}
		for (int i = 0; i < RunModel.Num_metro_stations; i++)
		{
			transport_buildings_vec.push_back(&Metro[i]);
		}
		for (int i = 0; i < RunModel.Num_airports; i++)
		{
			transport_buildings_vec.push_back(&Airport[i]);
		}

		static Model_Data model_data;
		
		int col_numbers = std::ceil(std::sqrt(RunModel.Num_Of_Tiles));
		int row_numbers = std::ceil((double)RunModel.Num_Of_Tiles / (double)col_numbers);

		Matrix<int> tile_matrix(row_numbers, col_numbers);

		int x = 0;
		int y = 0;
		for (int i = 0; i < RunModel.Num_Of_Tiles; i++)
		{
			tile_matrix.MatrixEdit(y+1, x+1, i);
			if (x + 1 == col_numbers)
			{
				x = 0;
				y++;
			}
			else
			{
				x++;
			}
		}

		model_data.counts = scenario_param.count;
		model_data.total = RunModel.population;
		
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

		std::fstream output_file;
		std::filesystem::path p(filename);
		std::string filename_new = "Output/" + p.stem().string() + ".cvo";
		std::string filenamenew = filename_new;
		
		bool exists = true;
		int num = 0;
		while (exists)
		{
			num++;
			if (std::filesystem::exists(filename_new))
			{
				std::filesystem::path p(filenamenew);
				filename_new = "Output/" + p.stem().string() + "(" + std::to_string(num) + ")" + ".cvo";
			}
			else
			{
				exists = false;
			}
		}

		output_file.open(filename_new, std::ios::out | std::ios::app);
		if (output_file.is_open())
		{
			output_file << "Scenario: " + filename << std::endl;
			output_file << model_data.R0 << std::endl;
			output_file << model_data.Sucept << std::endl;
			output_file << model_data.Infected << std::endl;
			output_file << model_data.Rec << std::endl;
			output_file << model_data.Host << std::endl;
			output_file << model_data.Dead << std::endl;
			output_file << model_data.mortality << std::endl;
			output_file << model_data.morbidity << std::endl;
		}
		output_file.close();

		for (int i = 0; i < RunModel.population; i++)
		{
			model_data.sucept.push_back(&actor[i]);
			actor_vec.push_back(&actor[i]);
			model_data.sucept[i]->set_stage(Actor::sucept);
		}

		{
			int x = 0;
			for (uint32_t i = 0; i < get_starting_infected(); i++)
			{
				x = Random::random_number(0, model_data.sucept.size(), {});
				actor_vec[x]->name = get_names()[0];
				actor_vec[x]->set_infectivity(get_infect());
				actor_vec[x]->set_recovery(get_recover());
				model_data.latent.push_back(model_data.sucept[x]);
				model_data.latent[i]->set_stage(Actor::latent);
				model_data.latent[i]->set_mortality(calculations::calc_mortaility(model_data.latent[i]->Get_age(), model_data.latent[i]->medical, model_data.latent[i]->race));
				model_data.sucept.erase(model_data.sucept.begin() + x);
			}

			for (int i = 1; i < get_names().size(); i++)
			{
				if (i != x)
				{
					actor_vec[i]->name = get_names()[i];
				}
			}
		}

		for (uint32_t i = 0; i < RunModel.Num_Of_Tiles; i++)
		{
			tiles_vec.push_back(&tiles[i]);
		}

		int count = 0;
		Director nick(actor_vec, tiles_vec, tile_matrix, *transport);
		nick.sleep_active = true;
		int day_count = 0;
		std::vector<Actor*> patients;

		std::vector<std::pair<Actor*, int>> infected_vector = {};
		std::vector<std::pair<Actor*, int>> infected_school = {};
		std::vector<std::pair<Actor*, int>> infected_public_building = {};
		std::vector<std::pair<Actor*, int>> infected_public_transport_building = {};
		std::vector<std::pair<Actor*, int>> infected_hospital = {};
		std::vector<std::pair<Actor*, int>> infected_gen_work = {};
		std::vector<std::pair<Actor*, int>> infected_transport = {};
		std::vector<std::pair<Actor*, int>> infected_outside = {};
		std::vector<std::pair<Actor*, int>> infected_homes = {};

		// The actual model
		//have a thread that finds agents.
		bool model_end = false;
		std::thread getagent(Model::get_agent, actor_vec, std::ref(model_end));
		bool exit = false;
		std::thread escape(Model::check_escape, std::ref(exit), std::ref(model_end));
		escape.detach();
		while (count != model_data.counts && exit == false)
		{
			//world tasks
			model_data.previous_infected = model_data.infected.size();
			model_data.previous_dead = model_data.dead.size();
			if(day_count == get_day_length())
			{
				day_count = 0;
			}
			if (day_count == 0)
			{
				nick.world_time = Tasks::morning;
			}
			else if (count == 600)
			{
				nick.world_time = Tasks::mid_morning;
			}
			else if (count == 720)
			{
				nick.world_time = Tasks::mid_day;
			}
			else if (count == 930)
			{
				nick.world_time = Tasks::afternoon;
			}
			else if (count == 1110)
			{
				nick.world_time = Tasks::early_evening;
			}
			else if (count == 1260)
			{
				nick.world_time = Tasks::late_evening;
			}

			if (day_count == 420 || day_count == 1320)
			{
				nick.world_task(Director::mandatory_task::idle);
				nick.world_task(Director::mandatory_task::sleep);
			}
			if (day_count == 480 || day_count == 840)
			{
				nick.world_task(Director::mandatory_task::go_to_work);
			}
			if (day_count == 720 || day_count == 1020)
			{
				nick.world_task(Director::mandatory_task::idle);
			}
			if (day_count == 1020)
			{
				nick.world_task(Director::mandatory_task::go_home);
			}

			if (nick.sleep_active == false)
			{
				if (nick.m_current_tasks.size() <= nick.max_actors_not_idle)
				{
					for (int i = 0; i < actor_vec.size(); i++)
					{
						if (actor_vec[i]->stage_check() == Actor::dead)
						{
							continue;
						}
						if (actor_vec[i]->hospital == true)
						{
							continue;
						}
						if (actor_vec[i]->symptoms == true)
						{
							continue;
						}
						if (actor_vec[i]->idle_counts > get_min_idle_time())
						{
							if (nick.m_current_tasks.size() <= nick.max_actors_not_idle)
							{
								bool ask = false;
								ask = actor_vec[i]->ask_director();
								if (ask == true || ask > 1)
								{
									nick.request_task(actor_vec[i]);
									actor_vec[i]->idle_counts = 0;
								}
								else
								{
									actor_vec[i]->idle_counts++;
								}
							}
						}
						else if (actor_vec[i]->idle_counts == get_max_idle_time())
						{
							nick.request_task(actor_vec[i]);
							actor_vec[i]->idle_counts = 0;
						}
						else
						{
							actor_vec[i]->idle_counts++;
							std::vector<unsigned int> weight = { 50,50 };
							if (Random::Discrete_distribution(weight, 1)[0] == 1)
							{
								actor_vec[i]->set_location_state(Actor::outside);
								actor_vec[i]->random_walk();
							}
						}
					}
				}
			}
			if (nick.m_current_tasks.size() > 0)
			{
				nick.run_tasks();
			}

			infected_vector.clear();
			infected_school.clear();
			infected_public_building.clear();
			infected_public_transport_building.clear();
			infected_hospital.clear();
			infected_gen_work.clear();
			infected_transport.clear();
			infected_outside.clear();

			if (nick.sleep_active != true)
			{
				std::thread schoolinfection(Model::education_building_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(schools_vec), std::ref(infected_school)); //education
				std::thread publicinfection(Model::building_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(public_buildings_vec), std::ref(infected_public_building));
				std::thread geninfection(Model::work_building_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(work_places), std::ref(infected_gen_work));
				std::thread transinfection(Model::transport_building_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(transport_buildings_vec), std::ref(infected_public_transport_building));
				std::thread hospitalinfection(Model::hospital_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(hospital_vec), std::ref(infected_hospital));
				std::thread transportinfection(Model::transport_infection, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(infected_transport));
				std::thread outsideinfection(Model::Infection_check_outside, std::ref(model_data.sucept), std::ref(model_data.infected), std::ref(infected_outside));

				schoolinfection.join();
				publicinfection.join();
				geninfection.join();
				transinfection.join();
				hospitalinfection.join();
				transportinfection.join();
				outsideinfection.join();
			}
			Model::home_building_infection(model_data.sucept, model_data.infected, houses, infected_vector);

			for (int i = 0; i < infected_school.size(); i++)
			{
				infected_vector.push_back(infected_school[i]);
			}
			for (int i = 0; i < infected_public_building.size(); i++)
			{
				infected_vector.push_back(infected_public_building[i]);
			}
			for (int i = 0; i < infected_gen_work.size(); i++)
			{
				infected_vector.push_back(infected_gen_work[i]);
			}
			for (int i = 0; i < infected_public_transport_building.size(); i++)
			{
				infected_vector.push_back(infected_public_transport_building[i]);
			}
			for (int i = 0; i < infected_hospital.size(); i++)
			{
				infected_vector.push_back(infected_hospital[i]);
			}
			for (int i = 0; i < infected_transport.size(); i++)
			{
				infected_vector.push_back(infected_transport[i]);
			}
			for (int i = 0; i < infected_outside.size(); i++)
			{
				infected_vector.push_back(infected_outside[i]);
			}

			std::sort(infected_vector.begin(), infected_vector.end(), functions::sortbysec);

			int size = infected_vector.size();
			int removed_actors = 0;
			for (int i = 0; i < size; i++)
			{
				int place = infected_vector[i].second;
				model_data.latent.push_back(model_data.sucept[place - removed_actors]);
				model_data.sucept[place - removed_actors]->set_stage(Actor::latent);
				model_data.sucept.erase(model_data.sucept.begin() + place - removed_actors);
				removed_actors++;
			}

			int latent_size = model_data.latent.size();
			for (int i = 0; i < latent_size; i++)
			{
				model_data.latent[i]->infection_length++;
				if (model_data.latent[i]->infection_length >= get_latent_time())
				{
					model_data.infected.push_back(model_data.latent[i - removed_actors]);
					model_data.latent[i - removed_actors]->set_stage(Actor::infect);
					model_data.latent.erase(model_data.latent.begin() + i - removed_actors );
					removed_actors++;
				}
			}

			model_data.now_infected = model_data.infected.size();

			std::vector<int> removed;
			for (int i = 0; i < model_data.infected.size(); i++)
			{
				model_data.infected[i]->infection_length++;
				if (model_data.infected[i]->get_infectivity_risk() == 0)
				{
					model_data.infected[i]->set_infectivity(get_infect());
					model_data.infected[i]->set_recovery(get_recover()); //temp
					model_data.infected[i]->set_mortality(calculations::calc_mortaility(model_data.infected[i]->Get_age(), model_data.infected[i]->medical, model_data.infected[i]->race));
				}
				if (model_data.infected[i]->symptoms == false)
				{
					bool symp = true;
					symp = model_data.infected[i]->show_symptoms();
					if (symp == false) { continue; }
				}
				else
				{
					if (model_data.infected[i]->Get_Location() != model_data.infected[i]->House_Location())
					{
						nick.go_home(model_data.infected[i]);
					}
				}

				if (model_data.infected[i]->hospital != true)
				{
					if (model_data.infected[i]->go_to_hospital() == true)
					{
						patients.push_back(model_data.infected[i]);
						model_data.hostipilized.push_back(model_data.infected[i]);
						continue;
					}
				}
				if (model_data.infected[i]->recover() == true)
				{
					if (model_data.infected[i]->hospital == true)
					{
						functions::remove_from_building(model_data.infected[i], tiles_vec);
					}
					model_data.recovered.push_back(model_data.infected[i]);
					removed.push_back(i);
					continue;
				}
				if (model_data.infected[i]->die() == true)
				{
					functions::remove_from_building(model_data.infected[i], tiles_vec);
					model_data.dead.push_back(model_data.infected[i]);
					removed.push_back(i);
					continue;
				}
			}

			model_data.now_dead = model_data.dead.size();
			nick.go_to_hospital(patients);
			for (int i = 0; i < removed.size(); i++)
			{
				model_data.infected.erase(model_data.infected.begin() + removed[i] - i);
			}
			removed.clear();
			patients.clear();
			//output
			std::thread output(functions::write_to_file, model_data, filename_new);

			for (int i = 0; i < tiles_vec.size(); i++)
			{
				for (int e = 0; e < tiles_vec[i]->Pub_buildings.size(); e++)
				{
					tiles_vec[i]->Pub_buildings[e]->check_closed();
				}
				for (int e = 0; e < tiles_vec[i]->edu_buildings.size(); e++)
				{
					tiles_vec[i]->edu_buildings[e]->check_closed();
				}
				for (int e = 0; e < tiles_vec[i]->Generic_work.size(); e++)
				{
					tiles_vec[i]->Generic_work[e]->check_closed();
				}
			}

			bool correct = false;
			int right = 0;
			while (correct == false)
			{
				for (int i = 0; i < model_data.sucept.size(); i++)
				{
					if (model_data.sucept[i]->stage_check() != Actor::sucept)
					{
						if (model_data.sucept[i]->stage_check() == Actor::latent)
						{
							model_data.latent.push_back(model_data.sucept[i]);
						}
						else if (model_data.sucept[i]->stage_check() == Actor::infect)
						{
							model_data.infected.push_back(model_data.sucept[i]);
						}
						model_data.sucept.erase(model_data.sucept.begin() + i);
						break;
					}
					else
					{
						right++;
					}
				}

				for (int i = 0; i < model_data.latent.size(); i++)
				{
					if (model_data.latent[i]->stage_check() != Actor::latent)
					{
						if (model_data.latent[i]->stage_check() == Actor::sucept)
						{
							model_data.sucept.push_back(model_data.latent[i]);
						}
						else if (model_data.latent[i]->stage_check() == Actor::infect)
						{
							model_data.infected.push_back(model_data.latent[i]);
						}
						model_data.latent.erase(model_data.sucept.begin() + i);
						break;
					}
					else
					{
						right++;
					}
				}

				if (right == model_data.latent.size() + model_data.sucept.size())
				{
					correct = true;
				}
			}
			//functions::write_to_file(model_data, filename_new);
			count++;
			day_count++;
			//std::cout << count << std::endl;
			output.join();
		}
		model_end = true;
		std::cout << "Model Finished" << std::endl;
		std::cout << "clear page" << std::endl;
		getagent.join();
		if (exit == false)
		{
			std::cout << "Press escape" << std::endl;
			escape.join();
		}
		model_log.LogFucntion(Log::LogLevelInfo, 5);

		//clean up code
		{
			for (int i = 0; i < houses.size(); i++)
			{
				delete houses[i];
			}
			houses.clear();

			for (int i = 0; i < work_places.size(); i++)
			{
				delete work_places[i];
			}
			work_places.clear();

			family_groups.clear();
			actor_vec.clear();
			tiles_vec.clear();

			delete[] actor;
			delete[] tiles;
			
			delete[] primary_school;
			delete[] secondry_school;
			delete[] further_education;
			
			delete[] Hospital;
			delete[] POW;
			delete[] Restuarant;
			delete[] Cinema;
			delete[] Shopping_center;
			delete[] Parks;

			delete[] Bus;
			delete[] Train;
			delete[] Metro;
			delete[] Airport;

			delete transport;
		}
	}
	else
	{
		std::cout << "failed" << std::endl;
	}
}

void Model::RunRandomModel()
{
	
}


void Model::Infection_check_outside(std::vector<Actor*>& sucept, std::vector<Actor*>& infected, std::vector<std::pair<Actor*, int>>& return_vector)
{
	std::vector<std::pair<Actor*, int>> infected_vec;
	for (int i = 0; i < infected.size(); i++)
	{
		if (infected[i]->get_location() != Actor::outside)
		{
			break;
		}
		auto [x, y, tile] = infected[i]->Get_Location();
		std::vector<std::pair<int, int>> infection_circle = functions::generate_circle(get_infection_distance(), std::make_pair(x, y));
		for (int a = 0; a < sucept.size(); a++)
		{
			auto [x1, y1, tile_num] = sucept[a]->Get_Location();
			if (tile_num == tile && sucept[a]->get_location() == Actor::outside && sucept[a]->stage_check() == Actor::sucept)
			{
				std::pair<int, int> location = { x1, y1 };
				std::vector<Actor*> temp;
				for (auto it : return_vector)
				{
					temp.push_back(it.first);
				}
				if (std::find(infection_circle.begin(), infection_circle.end(), location) != infection_circle.end() && std::find(temp.begin(), temp.end(), sucept[a]) == temp.end())
				{
					bool infection = false;
					double infection_chance = calculations::infection_prob(infected[i]->get_infectivity_risk(), infected[i]->get_severity());
					
					std::vector<double> weight_vector = { infection_chance, (1 - infection_chance) };
					if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
					{
						return_vector.push_back(std::make_pair(sucept[a], a));
					}
				}
			}
		}
	}
}

void Model::hospital_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_Buildings*>& Hospital, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	for (int i = 0; i < Hospital.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection = 0;
		for (int e = 0; e < Hospital[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), Hospital[i]->Get_people_currently_in_buildling()[e]) != infected_vec.end())
			{
				double modifier = 1;
				if (Hospital[i]->Get_people_currently_in_buildling()[e]->hospital == true)
				{
					modifier = 0.25;
				}
				infection = infection + (Hospital[i]->Get_people_currently_in_buildling()[e]->get_infectivity_risk() * modifier);
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		total_infected = total_infected + infected;
		infection = infection / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < Hospital[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (Hospital[i]->Get_people_currently_in_buildling()[e]->stage_check() == Actor::sucept)
			{
				double infection_chance = calculations::infection_prob(infection, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, Hospital[i]->Get_people_currently_in_buildling()[e]);
					if (out.second == true)
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
					//sucept[x]->set_stage(Actor::infect);
					//infected_vec.push_back(sucept[x]);
					//sucept.erase(sucept.begin() + x);
				}
			}
		}
	}
}

void Model::transport_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_transport_building*>& building, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	std::vector<std::pair<Actor*, int>> infected_vec_trans;
	for (int i = 0; i < building.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection_chance = 0;
		for (int e = 0; e < building[i]->Get_people_currently_in_building().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), building[i]->Get_people_currently_in_building()[e]) != infected_vec.end())
			{
				infection_chance = infection_chance + building[i]->Get_people_currently_in_building()[e]->get_infectivity_risk();
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		infection_chance = infection_chance / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < building[i]->Get_people_currently_in_building().size(); e++)
		{
			if (building[i]->Get_people_currently_in_building()[e]->stage_check() == Actor::sucept)
			{
				infection_chance = calculations::infection_prob(infection_chance, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, building[i]->Get_people_currently_in_building()[e]);
					if (out.second == true)
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
				}
			}
		}
	}
}

void Model::transport_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int infected_agents = 0;
	double infection = 0;
	std::vector<std::pair<Actor*, int>> infect_vec;
	for (int i = 0; i < infected.size(); i++)
	{
		if (infected[i]->state_check() != Actor::transit)
		{
			continue;
		}
		else
		{
			infection = infection + infected[i]->get_infectivity_risk();
			infected_agents++;
		}
	}

	if (infected_agents == 0)
	{
		return;
	}

	infection = infection / (double)infected_agents;

	double modifier = calculations::transport_infection_modifier(infected_agents);

	for (int i = 0; i < sucept.size(); i++)
	{
		if (sucept[i]->stage_check() == Actor::sucept && sucept[i]->state_check() == Actor::transit)
		{
			double infection_chance = calculations::infection_prob(infection, Actor::default_severity);
			infection_chance = infection_chance * modifier;

			std::vector<double> weight_vector = { infection_chance, (1 - infection_chance) };
			if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
			{
				return_vector.push_back(std::make_pair(sucept[i], i));
			}
		}
	}
}

void Model::education_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Education_Buildings*>& building, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	for (int i = 0; i < building.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection_chance = 0;
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), building[i]->Get_people_currently_in_buildling()[e]) != infected_vec.end())
			{
				infection_chance = infection_chance + building[i]->Get_people_currently_in_buildling()[e]->get_infectivity_risk();
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		infection_chance = infection_chance / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (building[i]->Get_people_currently_in_buildling()[e]->stage_check() == Actor::sucept)
			{
				infection_chance = calculations::infection_prob(infection_chance, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, building[i]->Get_people_currently_in_buildling()[e]);
					if (out.second == true)
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
				}
			}
		}
	}
}

void Model::work_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Generic_work*>& building, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	for (int i = 0; i < building.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection_chance = 0;
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), building[i]->Get_people_currently_in_buildling()[e]) != infected_vec.end())
			{
				infection_chance = infection_chance + building[i]->Get_people_currently_in_buildling()[e]->get_infectivity_risk();
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		infection_chance = infection_chance / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (building[i]->Get_people_currently_in_buildling()[e]->stage_check() == Actor::sucept)
			{
				infection_chance = calculations::infection_prob(infection_chance, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, building[i]->Get_people_currently_in_buildling()[e]);
					if (out.second == true)
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
				}
			}
		}
	}
}

void Model::home_building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<House*>& building, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	for (int i = 0; i < building.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection_chance = 0;
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), building[i]->Get_people_currently_in_buildling()[e]) != infected_vec.end())
			{
				infection_chance = infection_chance + building[i]->Get_people_currently_in_buildling()[e]->get_infectivity_risk();
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		infection_chance = infection_chance / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (building[i]->Get_people_currently_in_buildling()[e]->stage_check() == Actor::sucept)
			{
				infection_chance = calculations::infection_prob(infection_chance, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, building[i]->Get_people_currently_in_buildling()[e]);
					if (out.second == true)
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
				}
			}
		}
	}
}

void Model::building_infection(std::vector<Actor*>& sucept, std::vector<Actor*>& infected_vec, std::vector<Public_Buildings*>& building, std::vector<std::pair<Actor*, int>>& return_vector)
{
	int total_infected = 0;
	for (int i = 0; i < building.size(); i++)
	{
		if (total_infected == infected_vec.size())
		{
			break;
		}
		int infected = 0;
		double infection_chance = 0;
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (std::find(infected_vec.begin(), infected_vec.end(), building[i]->Get_people_currently_in_buildling()[e]) != infected_vec.end())
			{
				infection_chance = infection_chance + building[i]->Get_people_currently_in_buildling()[e]->get_infectivity_risk();
				infected++;
			}
		}

		if (infected == 0)
		{
			continue;
		}

		infection_chance = infection_chance / (double)infected;

		double infection_modifer = calculations::building_infection_modifier(infected);
		for (int e = 0; e < building[i]->Get_people_currently_in_buildling().size(); e++)
		{
			if (building[i]->Get_people_currently_in_buildling()[e]->stage_check() == Actor::sucept)
			{
				infection_chance = calculations::infection_prob(infection_chance, Actor::default_severity);
				double infection_prob = infection_chance * infection_modifer;
				if (infection_prob >= 0.9)
				{
					infection_prob = 0.9;
				}
				std::vector<double> weight_vector = { infection_prob, 1 - infection_prob };
				if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
				{
					std::pair<int, bool> out;
					out = functions::find_in_vec(sucept, building[i]->Get_people_currently_in_buildling()[e]);
					if (out.second == true) 
					{
						return_vector.push_back(std::make_pair(sucept[out.first], out.first));
					}
				}
			}
		}
	}
}


std::string Model::Get_filename(std::string& file_name)
{
	std::string filename;

	std::cout << "Scenario filename: ";
	std::cin >> filename;
	file_name = filename;
	return filename;
}

void Model::get_agent(const std::vector<Actor*> agents, const bool& leave)
{
	while (leave == false)
	{
		int choice = 0;
		system("CLS");
		std::cout << "name(0) or number(1): ";
		if (leave == true)
		{
			break;
		}
		std::cin >> choice;

		if (choice == 1)
		{
			int num = 0;
			std::cout << "Starting from 0 and up to " << agents.size() - 1 << std::endl;
			std::cout << "Number: ";
			std::cin >> num;

			agents[num]->show();
		}
		if (choice == 0)
		{
			std::string Name;
			std::cout << "Name: ";
			std::cin >> Name;

			std::vector<int> results;
			for (int i = 0; i < agents.size(); i++)
			{
				if (agents[i]->name == Name)
				{
					results.push_back(i);
				}
			}

			int result_num = 0;
			if (results.size() == 0) { continue; }
			std::cout << Name << " returned " << results.size() << " results. Which one, start at 0 and go up to " << results.size() - 1 <<" : ";
			std::cin >> result_num;
			agents[results[result_num]]->show();
		}
		int clear = 0;
		std::cout << "Clear? Yes(0) or No(1): ";
		std::cin >> clear;
	}
}

void Model::check_escape(bool& escape, const bool& model_end)
{
	while (GetAsyncKeyState(VK_ESCAPE) == 0 || model_end == true)
	{

	}
	escape = true;

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
					points.push_back(std::make_pair((center.first + radius - y), (center.second + radius - x - i)));
				}
				current_location.first = center.first + radius - y;
				current_location.second = center.second + radius - x;
			}
			else
			{
				for (int i = 0; i < radius + x + 1; i++)
				{
					points.push_back(std::make_pair((center.first - radius + y), (center.second + radius + x - i)));
				}
				current_location.first = center.first - radius + y;
				current_location.second = center.second + radius + x;
			}
		}
		else
		{
			if (x >= 0)
			{
				for (int i = 0; i < radius - x + 1; i++)
				{
					
					points.push_back(std::make_pair((center.first + radius + y), (center.second - radius + x + i)));
					
				}
				current_location.first = center.first + radius + y;
				current_location.second = center.second - radius + x;
			}
			else
			{
				for (int i = 0; i < radius + x + 1; i++)
				{
					
					points.push_back(std::make_pair((center.first - radius - y), (center.second - radius - x + i)));
					
				}
				current_location.first = center.first - radius - y;
				current_location.second = center.second - radius - x;
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
		//loop_complete = true;

	}

	return points;
}

std::pair<int, bool> functions::find_in_vec(const std::vector<Actor*>& vector, const Actor* value)
{
	bool found = false;
	int position = 0;
	while (found == false)
	{
		if (position == vector.size())
		{
			return std::make_pair(position, false);
		}
		else if (value == vector[position])
		{
			return std::make_pair(position, true);
		}
		else
		{
			position++;
		}
	}
	return std::make_pair(position, false);
}

void functions::write_to_file(const Model_Data& data, std::string filename)
{
	std::fstream output_file;
	std::filesystem::path p(filename);
	filename = "Output/" + p.stem().string();

	if (data.R0 == 1)
	{
		output_file.open(filename + " R0.cvo", std::ios::out | std::ios::app);
		if (data.previous_infected == 0)
		{
			output_file << "0" << std::endl;
		}
		else
		{
			output_file << std::to_string(calculations::R_0(data.previous_infected, data.now_infected)) << std::endl;
		}
		output_file.close();
	}
	if (data.Sucept == 1)
	{
		output_file.open(filename + " succept.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(data.sucept.size()) << std::endl;
		output_file.close();
	}
	if (data.Infected == 1)
	{
		output_file.open(filename + " infected.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(data.infected.size()) << std::endl;
		output_file.close();
	}
	if (data.Rec == 1)
	{
		output_file.open(filename + " recovered.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(data.recovered.size()) << std::endl;
		output_file.close();
	}
	if (data.Host == 1)
	{
		output_file.open(filename + " host.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(data.hostipilized.size()) << std::endl;
		output_file.close();
	}
	if (data.Dead == 1)
	{
		output_file.open(filename + " dead.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(data.dead.size()) << std::endl;
		output_file.close();
	}
	if (data.mortality == 1)
	{
		output_file.open(filename + " mortality.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(calculations::rate(data.total, data.previous_dead, data.now_dead)) << std::endl;
		output_file.close();
	}
	if (data.morbidity == 1)
	{
		output_file.open(filename + " morbidity.cvo", std::ios::out | std::ios::app);
		output_file << std::to_string(calculations::rate(data.total, data.previous_infected, data.now_infected)) << std::endl;
		output_file.close();
	}
	//std::cout << "task finished" << std::endl;
}

bool functions::sortbysec(const std::pair<Actor*, int>& a, const std::pair<Actor*, int>& b)
{
	return (a.second < b.second);
}


bool functions::remove_from_building(Actor* agent, std::vector<Tile*> tile_vec)
{
	int tilenum = std::get<2>(agent->Get_Location());
	agent->set_location_state(Actor::outside);
	for (int i = 0; i < tile_vec[tilenum]->Pub_buildings.size(); i++)
	{
		if (tile_vec[tilenum]->Pub_buildings[i]->Get_Location() == agent->Get_Location())
		{
			for (int a = 0; a < tile_vec[tilenum]->Pub_buildings[i]->Get_people_currently_in_buildling().size(); a++)
			{
				if (tile_vec[tilenum]->Pub_buildings[i]->Get_people_currently_in_buildling()[a] == agent)
				{
					tile_vec[tilenum]->Pub_buildings[i]->Get_people_currently_in_buildling().erase(tile_vec[tilenum]->Pub_buildings[i]->Get_people_currently_in_buildling().begin() + a);
					return true;
				}
			}
		}
	}

	for (int i = 0; i < tile_vec[tilenum]->edu_buildings.size(); i++)
	{
		if (tile_vec[tilenum]->edu_buildings[i]->Get_Location() == agent->Get_Location())
		{
			for (int a = 0; a < tile_vec[tilenum]->edu_buildings[i]->Get_people_currently_in_buildling().size(); a++)
			{
				if (tile_vec[tilenum]->edu_buildings[i]->Get_people_currently_in_buildling()[a] == agent)
				{
					tile_vec[tilenum]->edu_buildings[i]->Get_people_currently_in_buildling().erase(tile_vec[tilenum]->edu_buildings[i]->Get_people_currently_in_buildling().begin() + a);
					return true;
				}
			}
		}
	}

	for (int i = 0; i < tile_vec[tilenum]->Generic_work.size(); i++)
	{
		if (tile_vec[tilenum]->Generic_work[i]->Get_Location() == agent->Get_Location())
		{
			for (int a = 0; a < tile_vec[tilenum]->Generic_work[i]->Get_people_currently_in_buildling().size(); a++)
			{
				if (tile_vec[tilenum]->Generic_work[i]->Get_people_currently_in_buildling()[a] == agent)
				{
					tile_vec[tilenum]->Generic_work[i]->Get_people_currently_in_buildling().erase(tile_vec[tilenum]->Generic_work[i]->Get_people_currently_in_buildling().begin() + a);
					return true;
				}
			}
		}
	}

	for (int i = 0; i < tile_vec[tilenum]->Houses.size(); i++)
	{
		if (tile_vec[tilenum]->Houses[i]->Get_Location() == agent->Get_Location())
		{
			for (int a = 0; a < tile_vec[tilenum]->Houses[i]->Get_people_currently_in_buildling().size(); a++)
			{
				if (tile_vec[tilenum]->Houses[i]->Get_people_currently_in_buildling()[a] == agent)
				{
					tile_vec[tilenum]->Houses[i]->Get_people_currently_in_buildling().erase(tile_vec[tilenum]->Houses[i]->Get_people_currently_in_buildling().begin() + a);
					return true;
				}
			}
		}
	}

	for (int i = 0; i < tile_vec[tilenum]->public_transport.size(); i++)
	{
		if (tile_vec[tilenum]->public_transport[i]->Get_Location() == agent->Get_Location())
		{
			for (int a = 0; a < tile_vec[tilenum]->public_transport[i]->Get_people_currently_in_building().size(); a++)
			{
				if (tile_vec[tilenum]->public_transport[i]->Get_people_currently_in_building()[a] == agent)
				{
					tile_vec[tilenum]->public_transport[i]->Get_people_currently_in_building().erase(tile_vec[tilenum]->public_transport[i]->Get_people_currently_in_building().begin() + a);
					return true;
				}
			}
		}
	}

	return false;
}
