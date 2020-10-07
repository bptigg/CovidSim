#include "Public_Transport.h"

Public_transport_building::Public_transport_building()
{
}

Public_transport_building::~Public_transport_building()
{
}

void Public_transport_building::Get_Location()
{
}

void Public_transport_building::Get_Node()
{
}

void Public_transport_building::Get_Type()
{
}

void Public_transport_building::Get_staff_num()
{
}

void Public_transport_building::Get_Staff()
{
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
