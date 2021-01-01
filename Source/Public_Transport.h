#pragma once
#include <vector>

#include "Actor.h"

class Actor;

class Public_transport_building
{
public:
	enum Type
	{
		Bus, Train, Metro, Airport, default_type
	};

	enum Style
	{
		Local /*Bus stop*/ = 0, Regional, default_style
	};
private:
	int m_x = 0;
	int m_y = 0;
	unsigned int m_tile_num = 0;

	unsigned int m_staff_amount = 0;

	Type m_type = default_type;
	Style m_style = default_style;

	std::vector<Actor*> m_staff = {};
	std::vector<Actor*> People_in_building = {};

public:
	Public_transport_building();
	~Public_transport_building();

	std::tuple<int, int, unsigned int> Get_Location();
	void Get_Node();
	Type Get_Type();
	
	unsigned int Get_staff_num();
	std::vector<Actor*> Get_Staff();
	void add_staff(Actor& staff);

	std::vector<Actor*> Get_people_currently_in_building();

	void set_type(Type type);
	void set_style(int style);
	void set_location(int x, int y, unsigned int tilenum);
	void set_staff(unsigned int staff);
	void add_people_buiding(Actor* entity);
	void remove_people_building(Actor* entity);
};



