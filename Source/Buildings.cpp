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
	std::tuple<int, int, unsigned int>loc = { m_x, m_y, m_tilenum };
	return loc;
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

void Public_Buildings::add_staff(Actor& staff_member)
{
	staff.push_back(&staff_member);
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

void Education_Buildings::add_students(Actor& student)
{
	students.push_back(&student);
}

void Education_Buildings::add_Staff(Actor& staff_member)
{
	staff.push_back(&staff_member);
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
	return m_staff;
}

unsigned int Public_Buildings::Get_capacity()
{
	return m_capacity;
}

std::vector<Actor*> Public_Buildings::Get_staff()
{
	return staff;
}

Education_Buildings::Education_Buildings()
{
}

Education_Buildings::~Education_Buildings()
{
}

std::vector<Actor*> Education_Buildings::Get_students()
{
	return students;
}

std::vector<Actor*> Education_Buildings::Get_staff()
{
	return staff;
}

unsigned int Education_Buildings::get_student_amount()
{
	return (m_capacity - m_staff);
}

unsigned int Education_Buildings::get_staff_amount()
{
	return m_staff;
}

House::House(std::vector<Actor*> family)
	:m_occupants(family)
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
	return m_employees;
}

void Generic_work::add_employees(Actor& employee)
{
	m_employees.push_back(&employee);
}
