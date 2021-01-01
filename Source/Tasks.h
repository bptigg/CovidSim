#pragma once
#include <tuple>
#include <vector>

#include "Public_Transport.h"
#include "Buildings.h"

struct Tasks
{
	enum Destination_Types
	{
		Hospitals = 0, POW, Restaurant, Cinema, Shopping_center, Parks
	};
	enum Time_of_day //when they are most likely to go
	{
		morning, mid_morning, mid_day, afternoon, early_evening, late_evening, all
	};
	/*0-4*/ 
	std::vector<std::tuple<Destination_Types, std::vector<Time_of_day>>>task0_4 = { {Parks, {all}} };
	/*5-17*/ 
	std::vector<std::tuple<Destination_Types, std::vector<Time_of_day>>>task5_17 = { {Parks, {morning, early_evening}}, {Cinema, {afternoon, early_evening}}, {Shopping_center, {all}}, {Restaurant, {mid_day, early_evening}}, {POW, {mid_morning, early_evening}} };
	/*18-64*/ 
	std::vector<std::tuple<Destination_Types, std::vector<Time_of_day>>>task18_64 = { {Parks, {morning, mid_day, early_evening, late_evening}}, {POW, {all}}, {Restaurant, {mid_day, early_evening, late_evening}}, {Cinema, {early_evening, late_evening}}, {Shopping_center, {mid_day, afternoon, early_evening}}, {Hospitals, {all}} };
	/*65+*/
	std::vector<std::tuple<Destination_Types, std::vector<Time_of_day>>>task65 = { {Parks, {mid_morning, mid_day, afternoon}}, {POW, {mid_morning}}, {Restaurant, {mid_day, early_evening}}, {Shopping_center, {mid_morning, mid_day}} };
};

struct Task
{
	std::tuple<int, int, int> location;
	std::tuple<Public_Buildings*, Education_Buildings*, Public_transport_building*, House*, Generic_work*> location_type;
	Tasks::Destination_Types destination;
	unsigned int task_length = 0; //counts
	unsigned int run_time = 0; 
};