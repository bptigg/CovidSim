#pragma once
#include <vector>

#include "Actor.h"

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

	void Get_Location();
	void Get_Node();
	void Get_Type();
	
	void Get_staff_num();
	void Get_Staff();

	void Get_people_in_building();
};



