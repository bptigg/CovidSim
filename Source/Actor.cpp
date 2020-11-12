#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::A_star_algorithim()
{
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

void Actor::directional_work()
{
}

void Actor::Social_distancing()
{
}

void Actor::set_infectivity()
{
}

void Actor::set_stage(Actor::Stage stage)
{
	m_stage = stage;
}

void Actor::set_hostpilization_risk()
{
}

void Actor::set_mortality()
{
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

void Actor::set_host_risk(double risk)
{
	m_host_risk = risk;
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

bool Actor::weighted_walk(std::pair<unsigned int, unsigned int> location)
{
	//int time_taken = 0;
	//bool destination_reached = false;
	Matrix<double> weighted_move_matrix = Get_move_matrix(location, false);
	std::vector<double> move_vector = weighted_move_matrix.GetRow(direction + 1);

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
	//time_taken++;

	if (m_x == location.first && m_y == location.second)
	{
		//destination_reached = true;
		//std::cout << time_taken << std::endl;
		return true;
	}
}

void Actor::go_to_place(std::tuple<int, int, int> destination)
{
}

Actor::State Actor::state_check()
{
	return m_state;
}

Actor::Stage Actor::stage_check()
{
	return m_stage;
}

void Actor::Get_Vehicle()
{
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

double Actor::get_host_risk()
{
	return m_host_risk;
}

Actor::Symptom_Severity Actor::get_infectivity_risk()
{
	return m_Sev;
}

