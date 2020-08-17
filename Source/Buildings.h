#pragma once

#include <tuple>
#include <vector>

#include "Actor.h"

class Buildings
{
private:
	int m_x = 0;
	int m_y = 0;
	unsigned int m_tilenum = 0;

	std::vector<Actor*> Currently_in_building = {};

public:
	Buildings();
	~Buildings();

	std::tuple<int, int, unsigned int> Get_Location();
	void Get_people_currently_in_buildling();
};

class Public_Buildings : Buildings
{
public:
	enum Type
	{
		Hospital = 0, Place_of_worship, restuarant, cinema, shopping_center, parks, default_type
	};
private:
	Type m_type = default_type;
	unsigned int m_staff = 0;
	unsigned int m_capacity = 0;
public:
	Public_Buildings();
	~Public_Buildings();

	Type Get_Type();
	unsigned int Get_num_staff();
	unsigned int Get_capacity();
};

class Education_Buildings : Buildings
{
public:
	enum edu_type
	{
		Primary_school = 0, Secondary_school, College, University, defualt_type
	};
private:
	edu_type m_type = defualt_type;
	unsigned int m_staff = 0;
	unsigned int m_capacity = 0;

	std::vector<Actor*> students;
	std::vector<Actor*> staff;
public:
	Education_Buildings();
	~Education_Buildings();

	std::vector<Actor*> Get_students();
	std::vector<Actor*> Get_staff();
};

class House : Buildings
{
private:
	std::vector<Actor*> occupants;
public:
	House();
	~House();

	std::vector<Actor*> Get_occupants();
};

class Generic_work : Buildings
{
private:
	std::vector <Actor*> employees;
public:
	Generic_work();
	~Generic_work();
	std::vector <Actor*> Get_employees();
};