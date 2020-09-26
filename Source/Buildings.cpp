#include "Buildings.h"

Buildings::Buildings()
{
}

Buildings::~Buildings()
{
}

void Buildings::set_type()
{
}

void Buildings::set_staff()
{
}

void Buildings::set_capacity()
{
}

void Buildings::set_location(int x, int y, unsigned int tile_num)
{
	m_x = x;
	m_y = y;
	m_tilenum = tile_num;
}

std::tuple<int, int, unsigned int> Buildings::Get_Location()
{
	return std::tuple<int, int, unsigned int>();
}

void Buildings::Get_people_currently_in_buildling()
{
}


void Public_Buildings::set_type(Public_Buildings::Type type)
{
	m_type = type;
}

void Public_Buildings::set_staff(unsigned int& staff_amount)
{
	m_staff = staff_amount;
}

void Public_Buildings::set_capacity(unsigned int& capacity_amount)
{
	m_capacity = capacity_amount;
}

void Education_Buildings::set_type(Education_Buildings::edu_type type)
{
	m_type = type;
}

void Education_Buildings::set_staff(unsigned int& staff_amount)
{
	m_staff = staff_amount;
}

void Education_Buildings::set_capacity(unsigned int& capacity_amount)
{
	m_capacity = capacity_amount;
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
