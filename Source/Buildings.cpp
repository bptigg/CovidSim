#include "Buildings.h"

Buildings::Buildings()
{
}

Buildings::~Buildings()
{
}



std::tuple<int, int, unsigned int> Buildings::Get_Location()
{
	return std::tuple<int, int, unsigned int>();
}

void Buildings::Get_people_currently_in_buildling()
{
}

Public_Buildings::Public_Buildings()
{
}

Public_Buildings::~Public_Buildings()
{
}

Public_Buildings::Type Public_Buildings::Get_Type()
{
	return Type();
}

unsigned int Public_Buildings::Get_num_staff()
{
	return 0;
}

unsigned int Public_Buildings::Get_capacity()
{
	return 0;
}

Education_Buildings::Education_Buildings()
{
}

Education_Buildings::~Education_Buildings()
{
}

std::vector<Actor*> Education_Buildings::Get_students()
{
	return std::vector<Actor*>();
}

std::vector<Actor*> Education_Buildings::Get_staff()
{
	return std::vector<Actor*>();
}

House::House()
{
}

House::~House()
{
}

std::vector<Actor*> House::Get_occupants()
{
	return std::vector<Actor*>();
}

Generic_work::Generic_work()
{
}

Generic_work::~Generic_work()
{
}

std::vector<Actor*> Generic_work::Get_employees()
{
	return std::vector<Actor*>();
}
