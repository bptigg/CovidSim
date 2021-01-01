#include "Constants.h"


uint32_t MAX_FAMILY_SIZE = 5;
uint32_t get_max_family_size()
{
	return MAX_FAMILY_SIZE;
}

uint32_t NUM_OF_HOUSEHOLDS_PER_BLOCK = 10;
uint32_t get_num_of_households_per_block()
{
	return NUM_OF_HOUSEHOLDS_PER_BLOCK;
}

uint32_t NUM_OF_OFFICES_PER_BLOCK = 2;
uint32_t get_num_of_offices_per_block()
{
	return NUM_OF_OFFICES_PER_BLOCK;
}

uint32_t MAX_OFFICE_SIZE = 150;
uint32_t get_max_office_size()
{
	return MAX_OFFICE_SIZE;
}


double PERCENTAGE_ASYMPTOMATIC = 25;
double get_percentage_asymptomatic()
{
	return PERCENTAGE_ASYMPTOMATIC;
}

double PERCENTAGE_MILD = 50;
double get_percentage_mild()
{
	return PERCENTAGE_MILD;
}

uint32_t INFECTION_DISTANCE = 2;
uint32_t get_infection_distance()
{
	return INFECTION_DISTANCE;
}

uint32_t STARTING_INFECTED = 1;
uint32_t get_starting_infected()
{
	return STARTING_INFECTED;
}

double ASYMPTOMATIC = 0.75;
double MILD = 1;
double FULL = 1.25;
double get_modifier_value(int value)
{
	switch (value)
	{
	case 0:
		return ASYMPTOMATIC;
		break;
	case 1:
		return MILD;
		break;
	case 2:
		return FULL;
		break;
	default:
		return 1;
		break;
	}
}

uint32_t MAX_IDLE_TIME = 100; //counts are in minutes, This doesn't work if the actor is asleep
uint32_t get_max_idle_time()
{
	return MAX_IDLE_TIME;
}

uint32_t MIN_IDLE_TIME = 50;
uint32_t get_min_idle_time()
{
	return MIN_IDLE_TIME;
}

uint32_t COUNTS_PER_DAY = 86400;
uint32_t get_counts_per_day()
{
	return COUNTS_PER_DAY;
}

double TIME_MODIFIER = 0.1;
double get_time_modifier()
{
	return TIME_MODIFIER;
}

unsigned int MAX_WALK = 1;
unsigned int get_max_walk()
{
	return MAX_WALK;
}

double CHANCE = 0.15;
double get_chance()
{
	return CHANCE;
}

uint32_t MIN_AYSMPTOMATIC_PERIOD = 10080;
uint32_t get_min_period()
{
	return MIN_AYSMPTOMATIC_PERIOD;
}

uint32_t MAX_AYSMPTOMATIC_PERIOD = 20160;
uint32_t get_max_period()
{
	return MAX_AYSMPTOMATIC_PERIOD;
}

uint32_t DAY_LENGTH = 1440;
uint32_t get_day_length()
{
	return DAY_LENGTH;
}

