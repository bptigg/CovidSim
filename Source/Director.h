#pragma once

#include "Tasks.h"
#include "Actor.h"
#include "Constants.h"
#include "Setup_info.h"

#include "Random.h"

#include <vector>
#include <map>

#include <algorithm>
#include <thread>
#include <memory>

class Director
{
public:
	enum class mandatory_task
	{
		sleep, go_to_work, go_home, idle
	};

	int failed = 0;
	bool sleep_active = false;
	Tasks::Time_of_day world_time = Tasks::all;

	std::vector<std::tuple<Task*, Actor*, int>> m_current_tasks;
	unsigned int max_actors_not_idle = 5000;
	//std::vector<std::tuple<Task*, Actor*, int>> m_current_tasks;
	std::vector<Actor*> m_outside;
	std::vector<Actor*> m_idle;
	std::vector<Actor*> m_transit;
	std::vector<Actor*> m_doing_task;
private:
	std::vector<Actor*> m_population;

	Matrix<int> m_tile_matrix;
	Transport_Net* m_transport_net;

	Tasks m_tasks;

	std::vector<Tile*> m_tiles;
private:

	bool task_permission(Actor::State state);

	void change_actor_location(Actor* actor, Task task, bool task_end);
	unsigned int generate_random_task(Actor::Age_Catagory age_cat, Tasks::Time_of_day time);
	std::tuple<std::tuple<int, int, int>, Public_Buildings*> public_task_setup(int& actor_tile, Tasks::Destination_Types location_type);

	bool find_in_vector(const std::vector<Actor*>& vector, int& position, const Actor* value);
	std::vector<double> task_weight_vector(const std::vector<std::tuple<Tasks::Destination_Types, std::vector<Tasks::Time_of_day>>>& task_vector, const Tasks::Time_of_day& time);
	void clear_task_vector();
public:
	Director(std::vector<Actor*>& population, std::vector<Tile*>& tiles, Matrix<int>& tile_matrix, Transport_Net& net);
	~Director();
	
	void request_task(Actor* requestee);
	void go_home(Actor* requestee);
	void world_task(mandatory_task task);
	void run_tasks();
	
	void go_to_hospital(std::vector<Actor*>& patients);
}; 
