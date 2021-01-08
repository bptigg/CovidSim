#pragma once

#include <tuple>
#include <vector>

#include "Actor.h"

class Buildings
{
public:
	bool closed = false;
private:
	int m_x = 0;
	int m_y = 0;
	unsigned int m_tilenum = 0;

	std::vector<Actor*> Currently_in_building = {};

public:
	~Buildings();

	std::tuple<int, int, unsigned int> Get_Location();
	std::vector<Actor*> Get_people_currently_in_buildling();

	void set_location(int x, int y, unsigned int tile_num);

	virtual void set_type();
	virtual void set_staff();
	virtual void set_capacity();
	void add_people_buiding(Actor* entity);
	void remove_people_building(Actor* entity);

	virtual void check_closed();
};

class Public_Buildings : public Buildings
{
public:
	enum Type
	{
		Hospital = 0, Place_of_worship, restuarant, cinema, shopping_center, parks, default_type
	};

	std::vector<Actor*> patients;
private:
	Type m_type = default_type;
	unsigned int m_staff = 0;
	unsigned int m_capacity = 0;

	std::vector<Actor*> staff;
public:
	Public_Buildings();
	~Public_Buildings();

	Type Get_Type();
	unsigned int Get_num_staff();
	unsigned int Get_capacity();
	std::vector<Actor*> Get_staff();

	void set_type(Type type);
	void set_staff(unsigned int& staff_amount);
	void check_closed();
	void set_capacity(unsigned int& capacity_amount);

	void add_staff(Actor& staff_member);
};

class Education_Buildings : public Buildings
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

	unsigned int get_student_amount();
	unsigned int get_staff_amount();

	void set_type(edu_type type);
	void set_staff(unsigned int& staff_amount);
	void check_closed();
	void set_capacity(unsigned int& capacity_amount);

	void add_students(Actor& student);
	void add_Staff(Actor& staff);
};


class House : public Buildings
{
private:
	std::vector<Actor*> m_occupants;
public:
	House(std::vector<Actor*> family);
	House();
	~House();

	std::vector<Actor*> Get_occupants();
};

class Generic_work : public Buildings
{
private:
	std::vector <Actor*> m_employees;
public:
	Generic_work();
	~Generic_work();
	std::vector <Actor*> Get_employees();
	void add_employees(Actor& employee);
	void check_closed();
};