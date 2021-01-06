#include "Actor.h"

double Actor::matrix_distance(node& start_node, node& end_node, Matrix<int> tile_matrix)
{
	std::pair<int, int> start_location = { 0,0 };
	int start_tile = std::get<2>(start_node.location);

	std::pair<int, int> end_location = { 0,0 };
	int end_tile = std::get<2>(end_node.location);

	int row = std::floor((double)start_tile / (double)tile_matrix.Get_num_col());
	int col = start_tile - (row * tile_matrix.Get_num_col());

	start_location = std::make_pair(row, col);

	row = std::floor((double)end_tile / (double)tile_matrix.Get_num_col());
	col = end_tile - (row * tile_matrix.Get_num_col());

	end_location = std::make_pair(row, col);

	double distance = std::sqrt(std::pow((start_location.first - end_location.first), 2) + std::pow((start_location.second - end_location.second), 2));
	return distance;
}

void Actor::show()
{
	std::cout << name << std::endl;
	std::cout << "Destination: " << std::get<0>(Destination) << " " << std::get<1>(Destination) << " " << std::get<2>(Destination) << std::endl;
	std::cout << "Location: " << m_x << " " << m_y << " " << m_tilenum << std::endl;

	switch(m_state)
	{
	case 0:
		std::cout << "State: " << "idle" << std::endl;
		break;
	case 1:
		std::cout << "State: " << "transit" << std::endl;
		break;
	case 2:
		std::cout << "State: " << "doing task" << std::endl;
		break;
	case 3:
		std::cout << "State: " << "waiting" << std::endl;
		break;
	default:
		break;
	}

	switch (m_stage)
	{
	case 0:
		std::cout << "Infection Stage: " << "Succeptible" << std::endl;
		break;
	case 1:
		std::cout << "Infection Stage: " << "Infected" << std::endl;
		break;
	case 2:
		std::cout << "Infection Stage: " << "Recovered" << std::endl;
		break;
	case 3:
		std::cout << "Infection Stage: " << "Hospitalized" << std::endl;
		break;
	case 4:
		std::cout << "Infection Stage: " << "Dead" << std::endl;
		break;
	default:
		break;
	}

	switch (m_age_range)
	{
	case 1:
		std::cout << "Age group: " << "zero to four" << std::endl;
		break;
	case 2:
		std::cout << "Age group: " << "five to seventeen" << std::endl;
		break;
	case 3:
		std::cout << "Age group: " << "eighteen to fourty nine" << std::endl;
		break;
	case 4:
		std::cout << "Age group: " << "fifty to sixty five" << std::endl;
		break;
	case 5:
		std::cout << "Age group: " << "sixty five plus" << std::endl;
		break;
	default:
		break;
	}
}

bool Actor::ask_director()
{

	std::vector<double> weights = { 1 - get_chance(), get_chance() };
	descision = Random::Discrete_distribution(weights, 1)[0];

	if (descision == 0)
	{
		return false;
	}
	if (descision == 1)
	{
		return true;
	}

	return false;
}

bool Actor::A_star_algorithim(Transport_Net* network, Matrix<int> tile_matrix)
{
	a_star_path.clear();
	Log a_star_log(Log::LogLevelInfo);

	int nearest_node = get_nearest_node(network, this->Get_Location());

	if (nearest_node == 0)
	{
		a_star_log.LogFucntion(Log::LogLevelWarning, 3);
		return false;
	}

	node start_node;

	int b = 0;
	for (auto elem : network->public_transport_network)
	{
		if (elem.first == nearest_node)
		{
			start_node.g_cost = 0;
			start_node.node_num = elem.first;
			start_node.location = elem.second.first;
			break;
		}

		b++;

		if (b == network->public_transport_network.size())
		{
			a_star_log.LogFucntion(Log::LogLevelWarning, 3);
			return false;
		}

	}

	b = 0;
	int nearest_to_end = get_nearest_node(network, Destination);

	if (nearest_to_end == 0)
	{
		a_star_log.LogFucntion(Log::LogLevelWarning, 3);
		return false;
	}

	node end_node;
	for (auto elem : network->public_transport_network)
	{
		if (elem.first == nearest_to_end)
		{
			end_node.location = elem.second.first;
			end_node.node_num = elem.first;
			break;
		}

		b++;

		if (b == network->public_transport_network.size())
		{
			a_star_log.LogFucntion(Log::LogLevelWarning, 3);
			return false;
		}

	}

	bool tile_heuristic = false;
	if (std::get<2>(start_node.location) == std::get<2>(end_node.location))
	{
		tile_heuristic = true;
	}

	if (tile_heuristic == true)
	{
		start_node.h_cost = std::floor(get_distance(start_node.location, end_node.location));
	}
	else
	{
		start_node.h_cost = std::floor(matrix_distance(start_node, end_node, tile_matrix));
	}

	start_node.previous_node_num = NULL;
	start_node.f_cost = start_node.h_cost;

	bool path_found = false;
	
	std::vector<std::pair<int, node*>> open_list;
	std::vector<node*> closed_list;

	int run = 0;

	node* current_node = new node;
	current_node = &start_node;
	open_list.push_back(std::make_pair(current_node->f_cost, &start_node));

	while (path_found == false)
	{
		std::vector<int> col_weights = network->TransportNetwork->GetCol(current_node->node_num);
		for (int i = 0; i < network->TransportNetwork->GetCol(current_node->node_num).size(); i++)
		{
			bool in_closed_list = false;
			if (i == current_node->node_num - 1)
			{
				continue;
			}
			else
			{
				node* graph_node = new node;
				graph_node->g_cost = col_weights[i];
				
				for (auto elem : network->public_transport_network)
				{
					if (elem.first == i+1)
					{
						graph_node->location = elem.second.first;
						graph_node->previous_node_num = current_node->node_num;
						graph_node->node_num = i + 1;

						if (tile_heuristic == true)
						{
							graph_node->h_cost = get_distance(graph_node->location, end_node.location);
						}
						else
						{
							graph_node->h_cost = matrix_distance(*graph_node, end_node, tile_matrix);
						}

						break;
					}
				}
				graph_node->f_cost = graph_node->g_cost + graph_node->h_cost;

				for (int a = 0; a < open_list.size(); a++)
				{
					if (graph_node->location == open_list[a].second->location)
					{
						if (graph_node->f_cost <= open_list[a].first)
						{
							open_list[a].first = graph_node->f_cost + open_list[0].first;
							open_list[a].second->f_cost = graph_node->f_cost + open_list[0].first;
							open_list[a].second->previous_node_num = graph_node->previous_node_num;
						}
					}
				}

				for (int a = 0; a< closed_list.size(); a++)
				{
					if (graph_node->location == closed_list[a]->location)
					{
						in_closed_list = true;
					}
				}

				if (graph_node->g_cost != 0 && in_closed_list == false)
				{
					open_list.push_back(std::make_pair(graph_node->f_cost, graph_node));
				}
				else
				{
					delete graph_node;
				}
			}
		}
		std::sort(open_list.begin(), open_list.end());
		closed_list.push_back(current_node);

		if (open_list[0].second != current_node)
		{
			current_node = open_list[0].second;

			int i = 0;
			for (i < open_list.size(); i++;)
			{
				if (open_list[i].second == current_node)
				{
					break;
				}
			}
			open_list.erase(open_list.begin() + i);
		}
		else
		{
			open_list.erase(open_list.begin());
			if (open_list.size() == 0)
			{
				a_star_log.LogFucntion(Log::LogLevelWarning, 3);
				return false;
			}
			current_node = open_list[0].second;
		}

		
		if (closed_list[run]->location == end_node.location)
		{
			path_found = true;
			break;
		}

		if (open_list.size() == 0)
		{
			a_star_log.LogFucntion(Log::LogLevelWarning, 3);
			return false;
		}
	
		run++;
	}

	int node_num = closed_list.back()->node_num;
	
	path_found = false;

	while (path_found == false)
	{
		for (int i = 0; i < closed_list.size(); i++)
		{
			if (closed_list[i]->node_num == node_num)
			{
				a_star_path.push_back({node_num, closed_list[i]->f_cost, Vehicle::default_vehicle });
				node_num = closed_list[i]->previous_node_num;

				if (closed_list[i]->node_num == start_node.node_num)
				{
					path_found = true;
				}

				break;
			}
		}
	}

	for (int i = 0; i < closed_list.size(); i++)
	{
		//delete closed_list[i];
	}
	closed_list.clear();

	m_a_star_path = true;
	return true;
	//I need to fix this but don't quite know how prob use a if statement
}

Matrix<double> Actor::Get_move_matrix(std::pair<unsigned int , unsigned int> destination, bool random)
{
	Matrix<double> move_matrix(4, 4);
	if (random == true)
	{
		for (int row = 0; row < move_matrix.Get_num_row(); row++)
		{
			int col = 0;
			while (col < move_matrix.Get_num_col())
			{
				move_matrix.MatrixEdit((row + 1), (col + 1), 0.25);
				col++;
			}
		}
		return move_matrix;
	}
	else
	{
		int change_in_x = destination.first - m_x;
		int change_in_y = destination.second - m_y;

		change_in_x = abs(change_in_x);
		change_in_y = abs(change_in_y);

		double x_change = (double)change_in_x / (double)tile_size;
		double y_change = (double)change_in_y / (double)tile_size;

		double x_weight = 0.5 - (x_change / 4);
		double y_weight = 0.5 - (y_change / 4);

		double a_x = x_change / 4;
		double a_y = y_change / 4;

		if (x_weight == 0.5)
		{
			x_weight = 0;
			a_x = 0;
		}
		if (y_weight == 0.5)
		{
			y_weight = 0;
			a_y = 0;
		}

		if (m_x == 0)
		{
			a_x = 0;
		}
		else if (m_x == tile_size)
		{
			a_x = 0;
		}

		if (m_y == 0)
		{
			a_y = 0;
		}
		else if (m_y == tile_size)
		{
			a_y = 0;
		}
		
		std::vector <double> row;
		if (m_x < destination.first)
		{
			if (m_y < destination.second)
			{
				row = { x_weight, a_x, y_weight, a_y };
			}
			else
			{
				row = { x_weight, a_x, a_y, y_weight };
			}
		}
		else
		{
			if (m_y < destination.second)
			{
				row = { a_x, x_weight, y_weight, a_y };
			}
			else
			{
				row = { a_x, x_weight, a_y, y_weight };
			}
		}

		int col_num = 0;
		int row_num = 0;
		while (row_num < 4)
		{
			col_num = 0;
			for (auto weight : row)
			{
				move_matrix.MatrixEdit(row_num + 1, col_num + 1, weight);
				col_num++;
			}
			row_num++;
		}

		return move_matrix;
	}
}

void Actor::Social_distancing()
{
}

int Actor::get_distance(std::tuple<int, int, unsigned int> loc_start, std::tuple<int, int, unsigned int> loc_end)
{
	int d_x = std::get<0>(loc_end) - std::get<0>(loc_start);
	int d_y = std::get<1>(loc_end) - std::get<1>(loc_start);

	double magnitude = std::sqrt(d_x*d_x + d_y*d_y);
	int distance = std::floor(magnitude);
	return distance;
}



int Actor::get_nearest_node(Transport_Net* network, std::tuple<int , int, int> location)
{
	std::vector<std::pair<double, int>> distance_to_node;
	for (auto elem : network->public_transport_network)
	{
		auto [x, y, tilenum] = elem.second.first;
		if (tilenum == std::get<2>(location))
		{
			int mag = get_distance(location, { x, y, tilenum });
			distance_to_node.push_back(std::make_pair(mag, elem.first));
		}
	}

	std::sort(distance_to_node.begin(), distance_to_node.end());

	if (distance_to_node.size() == 0)
	{
		return 0;
	}
	return distance_to_node[0].second;
}


void Actor::set_infectivity(double infectivity)
{
	m_infectivity = infectivity;
}

void Actor::set_stage(Actor::Stage stage)
{
	m_stage = stage;
}

void Actor::set_hostpilization_risk(double risk)
{
	m_hostiplization_risk = risk;
}

void Actor::set_mortality(double risk)
{
	m_mortality_risk = risk;
}

void Actor::set_recovery(double risk)
{
	m_chance_of_recovery = risk;
}

void Actor::set_work_location(std::tuple<int, int, unsigned int> work)
{
	Work_coord = work;
}

void Actor::set_home_location(std::tuple<int, int, unsigned int> home)
{
	House_coord = home;
}

void Actor::set_location(unsigned int x, unsigned int y, unsigned int tile_num)
{
	m_x = x;
	m_y = y;
	m_tilenum = tile_num;
}

void Actor::set_location_state(Actor::Location location_state)
{
	location = location_state;
}

bool Actor::show_symptoms()
{
	if (infection_length < get_min_period() || infection_length > get_max_period())
	{
		return false;
	}
		
	double prob = ((double)infection_length - (double)get_min_period()) / ((double)get_max_period() - (double)get_min_period());
	std::vector<double> weight_vector = { prob, 1 - prob };
	
	if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
	{
		return true;
		symptoms = true;
	}
	return false;
}

bool Actor::go_to_hospital()
{
	std::vector<double> weight_vector = { m_hostiplization_risk, 1 - m_hostiplization_risk };
	if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
	{
		m_stage = Host;
		hospital = true;
		return true;
	}
	return false;
}

bool Actor::recover()
{
	std::vector<double> weight_vector = { m_chance_of_recovery, 1 - m_chance_of_recovery };
	if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
	{
		m_stage = rec;
		return true;
	}
	return false;
}

bool Actor::die()
{
	std::vector<double> weight_vector = { m_mortality_risk, 1 - m_mortality_risk };
	if (Random::Discrete_distribution(weight_vector, 1)[0] == 0)
	{
		m_stage = dead;
		return true;
	}
	return false;
}

void Actor::Age(Age_Catagory age)
{
	m_age_range = age;
}

void Actor::set_symptom_severity(unsigned int severity)
{
	switch (severity)
	{
	case 0:
		m_Sev = Actor::asymptomatic;
		break;
	case 1:
		m_Sev = Actor::mildely_symptomatic;
		break;
	case 2:
		m_Sev = Actor::full_symptoms;
		break;
	default:
		break;
	}
}

void Actor::random_walk()
{
	Matrix<double> random_move_matrix = Get_move_matrix(std::make_pair(0, 0), true);
	std::vector<double> move_vector = random_move_matrix.GetRow(direction + 1);
	
	direction = Random::Discrete_distribution(move_vector, 1)[0];
	switch (direction)
	{
	case 0:
		if (m_x >= tile_size)
		{
			m_x = m_x - 1;
			direction = 1;
			break;
		}
		m_x = m_x + 1;
		direction = 0;
		break;
	case 1:
		if (m_x <= 0)
		{
			m_x = m_x + 1;
			direction = 0;
			break;
		}
		m_x = m_x - 1;
		direction = 1;
		break;
	case 2:
		if (m_y >= tile_size)
		{
			m_y = m_y - 1;
			direction = 3;
			break;
		}
		m_y = m_y + 1;
		direction = 2;
		break;
	case 3:
		if (m_y <= 0)
		{
			m_y = m_y + 1;
			direction = 2;
			break;
		}
		m_y = m_y - 1;
		direction = 3;
		break;
	default:
		break;
	}
}

bool Actor::weighted_walk(std::pair<unsigned int, unsigned int> location)
{
	//int time_taken = 0;
	//bool destination_reached = false;
	Matrix<double> weighted_move_matrix = Get_move_matrix(location, false);
	std::vector<double> move_vector = weighted_move_matrix.GetRow(direction + 1);

	int num_zero = 0;
	for (int i = 0; i < move_vector.size(); i++)
	{
		if (move_vector[i] == 0)
		{
			num_zero++;
		}
	}
	
	if (num_zero != move_vector.size())
	{
		direction = Random::Discrete_distribution(move_vector, 1)[0];
		switch (direction)
		{
		case 0:
			m_x = m_x + 1;
			direction = 0;
			break;
		case 1:
			m_x = m_x - 1;
			direction = 1;
			break;
		case 2:
			m_y = m_y + 1;
			direction = 2;
			break;
		case 3:
			m_y = m_y - 1;
			direction = 3;
			break;
		default:
			break;
		}
	}
	//time_taken++;

	if (m_x == location.first && m_y == location.second)
	{
		//destination_reached = true;
		//std::cout << time_taken << std::endl;
		return true;
	}
}

bool Actor::go_to_place(std::tuple<int, int, int> destination, Transport_Net* network, Matrix<int> tile_matrix)
{
	Destination = destination;
	if (location == outside && get_distance(this->Get_Location(), destination) <= get_max_walk() && std::get<2>(this->Get_Location()) == std::get<2>(destination))
	{
		A_star_found = true;
		location = Actor::outside;
		if (weighted_walk({ std::get<0>(destination), std::get<1>(destination) }) == true)
		{
			return true;
		}
	}
	else
	{
		if (m_a_star_path == false)
		{

			A_star_found = A_star_algorithim(network, tile_matrix);
			if (A_star_found == false)
			{
				return false;
			}
		}
		if (m_start_node == false)
		{
			location = Actor::outside;
			auto node = network->public_transport_network.find(std::get<0>(a_star_path[0]));
			std::tuple start_node = node->second.first;
			if (weighted_walk({ std::get<0>(start_node), std::get<1>(start_node) }) == true)
			{
				m_start_node = true;
			}
		}
		if (m_end_point == true)
		{
			location = Actor::outside;
			weighted_walk({ std::get<0>(destination), std::get<1>(destination) });
		}

		if (m_start_node == true && m_end_point != true)
		{
			location = Actor::in_transit;
			int delay = std::get<1>(a_star_path[point_in_path]);
			weight_count++;
			if (weight_count == delay || point_in_path == 0)
			{
				auto node = network->public_transport_network.find(std::get<0>(a_star_path[point_in_path]));
				m_x = std::get<0>(node->second.first);
				m_y = std::get<1>(node->second.first);
				m_tilenum = std::get<2>(node->second.first);
				weight_count = 0;
				point_in_path++;
			}

			if(point_in_path == a_star_path.size())
			{
				m_end_point = true;
			}
		}

		if (Get_Location() == destination)
		{
			m_a_star_path = false;
			m_start_node = false;
			m_end_point = false;
			point_in_path = 0;
			if (destination == House_coord)
			{
				location = Actor::home;
			}
			else if (destination == Work_coord)
			{
				location = Actor::work;
			}
			else
			{
				location = Actor::unkown;
			}
			return true;
		}
		else
		{
			return false;
		}

		//do weighted walk to start location and then run the path then walk to the end node
	}
	return false;
}

Actor::State Actor::state_check()
{
	return m_state;
}

void Actor::set_state(Actor::State state)
{
	m_state = state;
}

Actor::Stage Actor::stage_check()
{
	return m_stage;
}

Actor::Vehicle Actor::Get_Vehicle()
{
	return m_mode_of_transport;
}

std::tuple<unsigned int, unsigned int, unsigned int> Actor::Get_Location()
{
	return { m_x, m_y, m_tilenum };
}

std::tuple<unsigned int, unsigned int, unsigned int> Actor::House_Location()
{
	return House_coord;
}

std::tuple<unsigned int, unsigned int, unsigned int> Actor::Work_Location()
{
	return Work_coord;
}

Actor::Age_Catagory Actor::Get_age()
{
	return m_age_range;
}

Actor::Location Actor::get_location()
{
	return location;
}

double Actor::get_infectivity_risk()
{

	return m_infectivity;
}

double Actor::get_hospilization_risk()
{
	return m_hostiplization_risk;
}

double Actor::get_mortality_risk()
{
	return m_mortality_risk;
}

Actor::Symptom_Severity Actor::get_severity()
{
	return m_Sev;
}

