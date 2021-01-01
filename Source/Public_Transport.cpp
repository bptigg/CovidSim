#include "Public_Transport.h"

Public_transport_building::Public_transport_building()
{
}

Public_transport_building::~Public_transport_building()
{
	m_staff.clear();
	People_in_building.clear();
}

std::tuple<int, int, unsigned int> Public_transport_building::Get_Location()
{
	std::tuple<int, int, unsigned int>loc = { m_x, m_y, m_tile_num};
	return loc;
}

void Public_transport_building::Get_Node()
{
}

Public_transport_building::Type Public_transport_building::Get_Type()
{
	return m_type;
}

unsigned int Public_transport_building::Get_staff_num()
{
	return m_staff_amount;
}

std::vector<Actor*> Public_transport_building::Get_Staff()
{
	return m_staff;
}

void Public_transport_building::add_staff(Actor& staff)
{
	m_staff.push_back(&staff);
}

std::vector<Actor*> Public_transport_building::Get_people_currently_in_building()
{
	return People_in_building;
}

void Public_transport_building::set_type(Type type)
{
	m_type = type;
}

void Public_transport_building::set_style(int style)
{
	m_style = style == 0 ? Local : Regional;
}

void Public_transport_building::set_location(int x, int y, unsigned int tilenum)
{
	m_x = x;
	m_y = y;
	m_tile_num = tilenum;
}

void Public_transport_building::set_staff(unsigned int staff)
{
	m_staff_amount = staff;
}

void Public_transport_building::add_people_buiding(Actor* entity)
{
	People_in_building.push_back(entity);
}

void Public_transport_building::remove_people_building(Actor* entity)
{
	for (int position = 0; position < People_in_building.size(); position++)
	{
		if (People_in_building[position] == entity)
		{
			People_in_building.erase(People_in_building.begin() + position);
			break;
		}
	}
}
