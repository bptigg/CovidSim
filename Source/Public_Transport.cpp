#include "Public_Transport.h"

Public_transport_building::Public_transport_building()
{
}

Public_transport_building::~Public_transport_building()
{
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

void Public_transport_building::Get_people_in_building()
{
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
