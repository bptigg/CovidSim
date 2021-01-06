#include "Director.h"


bool Director::task_permission(Actor::State state)
{
	if (state == Actor::idle && m_current_tasks.size() <= max_actors_not_idle && sleep_active == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Director::change_actor_location(Actor* actor, Task task, bool task_end)
{
	auto [public_Buildings, education_Buildings, public_transport_building, house, generic_work] = task.location_type;
	if (task_end != true)
	{
		if (public_Buildings != NULL)
		{
			std::get<0>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::public_building);
			return;
		}
		if (education_Buildings != NULL)
		{
			std::get<1>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::work);
			return;
		}
		if (public_transport_building != NULL)
		{
			std::get<2>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::work);
			return;
		}
		if (house != NULL)
		{
			std::get<3>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::home);
			return;
		}
		if (generic_work != NULL)
		{
			std::get<4>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::work);
			return;
		}
	}
	else
	{
		if (public_Buildings != NULL)
		{
			std::get<0>(task.location_type)->remove_people_building(actor);
			actor->set_location_state(Actor::outside);
			return;
		}
		if (education_Buildings != NULL)
		{
			std::get<1>(task.location_type)->remove_people_building(actor);
			actor->set_location_state(Actor::outside);
			return;
		}
		if (public_transport_building != NULL)
		{
			std::get<2>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::outside);
			return;
		}
		if (house != NULL)
		{
			std::get<3>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::outside);
			return;
		}
		if (generic_work != NULL)
		{
			std::get<4>(task.location_type)->add_people_buiding(actor);
			actor->set_location_state(Actor::outside);
			return;
		}
	}
}

void Director::world_task(mandatory_task task)
{
	clear_task_vector();
	mandatorytask = true;
	if (task != mandatory_task::sleep)
	{
		for (auto actor : m_population)
		{
			if (task == mandatory_task::go_home)
			{
				Task* task = new Task;
				int x = std::get<0>(actor->House_Location());
				int y = std::get<1>(actor->House_Location());
				int tile_num = std::get<2>(actor->House_Location());
				int i = 0;
				for (i < m_tiles[tile_num]->Houses.size(); i++;)
				{
					if (m_tiles[tile_num]->Houses[i]->Get_Location() == actor->House_Location())
					{
						break;
					}
				}
				task->location_type = { NULL, NULL, NULL, m_tiles[tile_num]->Houses[i], NULL };
				task->location = actor->House_Location();

				int delay = Random::random_number(0, 10, {});

				actor->set_state(Actor::waiting);
				m_current_tasks.push_back({ task, actor, delay });
			}
			else if (task == mandatory_task::go_to_work)
			{
				Task* task = new Task;
				int x = std::get<0>(actor->Work_Location());
				int y = std::get<1>(actor->Work_Location());
				int tile_num = std::get<2>(actor->Work_Location());
				//Generic_work* work = new Generic_work;
				//Education_Buildings* school = new Education_Buildings;
				//Public_Buildings* Work = new Public_Buildings;
				//Public_transport_building* work_public_transport = new Public_transport_building;

				bool found = false;
				int i = 0;
				for (i < m_tiles[tile_num]->Generic_work.size(); i++;)
				{
					if (m_tiles[tile_num]->Generic_work[i]->Get_Location() == actor->Work_Location())
					{
						found = true;
					}
				}

				if (found == true)
				{
					task->location_type = { NULL, NULL, NULL, NULL, m_tiles[tile_num]->Generic_work[i] };
				}
				else
				{
					i = 0;
					for (i < m_tiles[tile_num]->edu_buildings.size(); i++;)
					{
						if (m_tiles[tile_num]->edu_buildings[i]->Get_Location() == actor->Work_Location())
						{
							found = true;
						}
					}
					if (found == true)
					{
						task->location_type = { NULL, m_tiles[tile_num]->edu_buildings[i], NULL, NULL, NULL };
					}
					else
					{
						i = 0;
						for (i < m_tiles[tile_num]->Pub_buildings.size(); i++;)
						{
							if (m_tiles[tile_num]->Pub_buildings[i]->Get_Location() == actor->Work_Location())
							{
								found = true;
							}
						}
						if (found == true)
						{
							task->location_type = { m_tiles[tile_num]->Pub_buildings[i], NULL, NULL, NULL, NULL };
						}
						else
						{
							int i = 0;
							for (i < m_tiles[tile_num]->public_transport.size(); i++;)
							{
								if (m_tiles[tile_num]->public_transport[i]->Get_Location() == actor->Work_Location())
								{
									found = true;
								}
							}
							if (found == true)
							{
								task->location_type = { NULL, NULL, m_tiles[tile_num]->public_transport[i], NULL, NULL };
							}
						}
					}
				}

				task->location = actor->Work_Location();

				int delay = Random::random_number(0, 10, {});
				std::tuple<int, int, int> null_tuple = { 0,0,0 };
				if (task->location != null_tuple)
				{
					actor->set_state(Actor::waiting);
					m_current_tasks.push_back({ task, actor, delay });
				}
				else
				{
					delete task;
				}
			}
			else if (task == mandatory_task::idle)
			{
			mandatorytask = false;
				int x = 0;
				if (actor->state_check() != Actor::idle)
				{
					actor->set_state(Actor::idle);
					actor->idle_counts = 0;
					if (actor->state_check() == Actor::in_transit && m_transit.size() != 0)
					{
						find_in_vector(m_transit, x, actor);
						m_transit.erase(m_transit.begin() + x);
						m_idle.push_back(actor);
						//actor->set_state(Actor::idle);
					}
					if (actor->state_check() == Actor::doing_task && m_doing_task.size() != 0)
					{
						find_in_vector(m_doing_task, x, actor);
						m_doing_task.erase(m_doing_task.begin() + x);
						m_idle.push_back(actor);
						//actor->set_state(Actor::idle);
					}
				}
			}
		}
	}
	else if (task == mandatory_task::sleep)
	{
		mandatorytask = false;
		if (sleep_active == false)
		{
			sleep_active = true;
		}
		else
		{
			sleep_active = false;
		}
	}
}

void Director::run_tasks()
{
	Log log_tasks(Log::LogLevelWarning);
	for (int i = 0; i < m_current_tasks.size(); i++)
	{
		if (std::get<2>(m_current_tasks[i]) == 0)
		{
			Actor* agent = std::get<1>(m_current_tasks[i]);
			if (agent->Get_Location() != std::get<0>(m_current_tasks[i])->location)
			{
				agent->go_to_place(std::get<0>(m_current_tasks[i])->location, m_transport_net, m_tile_matrix);
				if (agent->A_star_found == false)
				{
					delete std::get<0>(m_current_tasks[i]);
					m_current_tasks.erase(m_current_tasks.begin() + i);
					log_tasks.LogFucntion(Log::LogLevelWarning, 4);
					failed++;
					continue;
				}
				continue;
			}
			if (agent->Get_Location() == std::get<0>(m_current_tasks[i])->location && agent->task_dest == false)
			{
				change_actor_location(agent, *std::get<0>(m_current_tasks[i]), false);
				agent->set_state(Actor::doing_task);
				agent->task_dest = true;
				int x = 0;
				//find_in_vector(m_transit, x, agent);
				//m_doing_task.push_back(agent);
				continue;
			}
			if (std::get<0>(m_current_tasks[i])->run_time == std::get<0>(m_current_tasks[i])->task_length && mandatorytask == false)
			{
				change_actor_location(agent, *std::get<0>(m_current_tasks[i]), true);
				agent->task_dest = false;
				m_current_tasks.erase(m_current_tasks.begin() + i);
				//m_idle.push_back(agent);
				continue;
			}
			else
			{
				std::get<0>(m_current_tasks[i])->run_time = std::get<0>(m_current_tasks[i])->run_time + 1;
			}
		}
		else
		{
			/*auto [task, agent, delay] = m_current_tasks[i];
			m_current_tasks.erase(m_current_tasks.begin() + i);
			m_current_tasks.push_back({ task, agent, delay - 1 });*/

			std::get<2>(m_current_tasks[i]) += -1;
		}

	}
	//std::cin.get();
}

void Director::go_to_hospital(std::vector<Actor*>& patients)
{
	for (int i = 0; i < patients.size(); i++)
	{
		uint32_t tile = 0;
		uint32_t tile_1 = tile;
		tile = std::get<2>(patients[i]->House_coord);

		bool hospital = false;
		bool no_hospital = false;
		while(hospital == false && no_hospital == false)
		{
			for (int e = 0; e < m_tiles[tile]->Pub_buildings.size(); e++)
			{
				if (m_tiles[tile]->Pub_buildings[e]->Get_Type() == Public_Buildings::Hospital)
				{
					if (m_tiles[tile]->Pub_buildings[e]->Get_people_currently_in_buildling().size() != m_tiles[tile]->Pub_buildings[e]->Get_capacity())
					{
						m_tiles[tile]->Pub_buildings[e]->patients.push_back(patients[i]);
						m_tiles[tile]->Pub_buildings[e]->add_people_buiding(patients[i]);
						patients[i]->m_x = std::get<0>(m_tiles[tile]->Pub_buildings[e]->Get_Location());
						patients[i]->m_y = std::get<1>(m_tiles[tile]->Pub_buildings[e]->Get_Location());
						patients[i]->m_tilenum = std::get<2>(m_tiles[tile]->Pub_buildings[e]->Get_Location());
						hospital = true;
						break;
					}
				} 
			}
			tile++;
			if (tile == m_tiles.size())
			{
				tile = 0;
			}
			if (tile == tile_1)
			{
				no_hospital = true;
			}
		}
		if (no_hospital == true)
		{
			patients[i]->hospital = false;
			break;
		}
	}
}

unsigned int Director::generate_random_task(Actor::Age_Catagory age_cat, Tasks::Time_of_day time)
{
	std::vector<unsigned int> task;
	if (age_cat == Actor::zero_to_four)
	{
		std::vector<double> weights = task_weight_vector(m_tasks.task0_4, time);
		task = Random::Discrete_distribution(weights, 1);
		return task[0];
	}
	else if (age_cat == Actor::five_to_seventeen)
	{
		std::vector<double> weights = task_weight_vector(m_tasks.task5_17, time);
		task = Random::Discrete_distribution(weights, 1);
		return task[0];
	}
	else if (age_cat == Actor::eighteen_to_fortynine || age_cat == Actor::fifty_to_sixtyfour)
	{
		std::vector<double> weights = task_weight_vector(m_tasks.task18_64, time);
		task = Random::Discrete_distribution(weights, 1);
		return task[0];
	}
	else
	{
		std::vector<double> weights = task_weight_vector(m_tasks.task65, time);
		task = Random::Discrete_distribution(weights, 1);
		return task[0];
	}
}

std::tuple<std::tuple<int, int, int>, Public_Buildings*> Director::public_task_setup(int& actor_tile, Tasks::Destination_Types location_type)
{
	int num_of_building_type = 0;
	std::vector<Public_Buildings*> public_buildings;
	switch (location_type)
	{
	case 0:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::Hospital)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	case 1:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::Place_of_worship)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	case 2:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::restuarant)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	case 3:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::cinema)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	case 4:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::shopping_center)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	case 5:
		for (int i = 0; i < m_tiles[actor_tile]->Pub_buildings.size(); i++)
		{
			if (m_tiles[actor_tile]->Pub_buildings[i]->Get_Type() == Public_Buildings::parks)
			{
				public_buildings.push_back(m_tiles[actor_tile]->Pub_buildings[i]);
			}
		}
		break;
	}

	int random_building = Random::random_number(0, public_buildings.size(), {});
	if (random_building != public_buildings.size())
	{
		return { m_tiles[actor_tile]->Pub_buildings[random_building]->Get_Location(), m_tiles[actor_tile]->Pub_buildings[random_building] };
	}
	else
	{
		std::vector<std::vector<Public_Buildings*>> public_buildings_tile;
		for (int32_t a = 0; a < m_tiles.size(); a++)
		{
			public_buildings.clear();
			if (a != actor_tile)
			{
				switch (location_type)
				{
				case 0:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::Hospital)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				case 1:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::Place_of_worship)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				case 2:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::restuarant)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				case 3:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::cinema)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				case 4:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::shopping_center)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				case 5:
					for (int i = 0; i < m_tiles[a]->Pub_buildings.size(); i++)
					{
						if (m_tiles[a]->Pub_buildings[i]->Get_Type() == Public_Buildings::parks)
						{
							public_buildings.push_back(m_tiles[a]->Pub_buildings[i]);
						}
					}
					public_buildings_tile.push_back(public_buildings);
					break;
				}
			}
		}
		bool empty_vec = true;
		int random_vec;
		std::vector<unsigned int> used_numbers = {};
		while (empty_vec == true)
		{
			random_vec = Random::random_number(0, public_buildings_tile.size() - 1, used_numbers);
			if (public_buildings_tile[random_vec].size() != 0)
			{
				empty_vec = false;
			}
			used_numbers.push_back(random_vec);
		}
		random_building = Random::random_number(0, public_buildings_tile[random_vec].size() - 1, {});
		return { public_buildings_tile[random_vec][random_building]->Get_Location(), public_buildings_tile[random_vec][random_building] };
	}
	return { {0,0,0}, NULL };
}

bool Director::find_in_vector(const std::vector<Actor*>& vector, int& position, const Actor* value)
{
	bool found = false;
	while (found == false)
	{
		if (position == vector.size())
		{
			return false;
		}
		else if (value == vector[position])
		{
			return true;
		}
		else
		{
			position++;
		}
	}
	return false;
}

std::vector<double> Director::task_weight_vector(const std::vector<std::tuple<Tasks::Destination_Types, std::vector<Tasks::Time_of_day>>>& task_vector, const Tasks::Time_of_day& time)
{
	std::vector<double> weight_vector;
	std::vector<int> extra;
	double extra_prob = 0;
	for (int i = 0; i < task_vector.size(); i++)
	{
		double a = 1 / task_vector.size();
		if (std::find(std::get<1>(task_vector[i]).begin(), std::get<1>(task_vector[i]).end(), time) != std::get<1>(task_vector[i]).end() || std::get<1>(task_vector[i])[0] == Tasks::all)
		{
			extra.push_back(i);
			extra_prob = extra_prob + get_time_modifier();
		}
	}

	double a = (1 - extra_prob) / task_vector.size();

	for (int i = 0; i < task_vector.size(); i++)
	{
		if (std::find(extra.begin(), extra.end(), i) == extra.end())
		{
			weight_vector.push_back(a);
		}
		else
		{
			weight_vector.push_back(a + get_time_modifier());
		}
	}

	return weight_vector;
}

void Director::clear_task_vector()
{
	for (int i = 0; i < m_current_tasks.size(); i++)
	{
		delete std::get<0>(m_current_tasks[i]);
	}
	m_current_tasks.clear();
}

Director::Director(std::vector<Actor*>& population, std::vector<Tile*>& tiles, Matrix<int>& tile_matrix, Transport_Net& net)
	:m_population(population), m_tiles(tiles), m_tile_matrix(tile_matrix), m_transport_net(&net), m_idle(population)
{
	for (int i = 0; i < population.size(); i++)
	{
		m_transit.push_back(NULL);
	}
	for (int i = 0; i < population.size(); i++)
	{
		m_doing_task.push_back(NULL);
	}
	for (int i = 0; i < population.size(); i++)
	{
		m_outside.push_back(NULL);
	}
	m_outside.clear();
	m_transit.clear();
	m_doing_task.clear();
}

Director::~Director()
{
}


void Director::request_task(Actor* requestee)
{
	bool permission = false;
	unsigned int task_value = 0;
	permission = task_permission(requestee->state_check());
	if (permission == true)
	{
		task_value = generate_random_task(requestee->Get_age(), world_time);
		int tile_number = std::get<2>(requestee->Get_Location());
		auto [location, building] = public_task_setup(tile_number, (Tasks::Destination_Types)task_value);
		int task_length = Random::random_number(20, 300, {});
		Task* task = new Task;
		task->destination = (Tasks::Destination_Types)task_value;
		task->location_type = { building, NULL, NULL, NULL, NULL };
		task->location = location;
		task->task_length = task_length;
		if (building->Get_people_currently_in_buildling().size() == building->Get_capacity())
		{
			delete task;
			
			int num = Random::random_number(0, 1, {});
			if (num == 1)
			{
				go_home(requestee);
			}
		}
		else
		{
			m_current_tasks.push_back({ task, requestee, 0 });
			requestee->set_state(Actor::waiting);
		}
	}
}

void Director::go_home(Actor* requestee)
{
	Task* task = new Task;
	auto [x, y, tile_num] = requestee->House_Location();
	House* home = NULL;
	for (int i = 0; i < m_tiles[tile_num]->Houses.size(); i++)
	{
		if (m_tiles[tile_num]->Houses[i]->Get_Location() == requestee->House_Location())
		{
			home = m_tiles[tile_num]->Houses[i];
		}
	}
	task->location_type = { NULL, NULL, NULL, home, NULL };
	task->location = requestee->House_Location();

	requestee->set_state(Actor::waiting);
	m_current_tasks.push_back({ task, requestee, 0});
}
