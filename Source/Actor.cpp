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

void Actor::Get_move_matrix()
{
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
}

void Actor::go_to_place()
{
}

void Actor::state_check()
{
}

void Actor::Get_Vehicle()
{
}

void Actor::Get_Location()
{
}

void Actor::House_Location()
{
}

void Actor::Work_Location()
{
}

Actor::Age_Catagory Actor::Get_age()
{
	return m_age_range;
}

