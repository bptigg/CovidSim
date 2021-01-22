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

uint32_t LATENT_TIME = 3600; //3600
uint32_t get_latent_time()
{
	return LATENT_TIME;
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

uint32_t MIN_AYSMPTOMATIC_PERIOD = 10080; //10080;
uint32_t get_min_period()
{
	return MIN_AYSMPTOMATIC_PERIOD;
}

uint32_t MAX_AYSMPTOMATIC_PERIOD = 20160; //20160;
uint32_t get_max_period()
{
	return MAX_AYSMPTOMATIC_PERIOD;
}

uint32_t DAY_LENGTH = 1440;
uint32_t get_day_length()
{
	return DAY_LENGTH;
}

std::vector<std::string> NAMES = { "Hugo", "Stephen", "Gage", "George", "Ryan", "Ben", "Arthur"};
std::vector <std::string> get_names()
{
	return NAMES;
}

//COVID VALUES (CURRENTLY TEMPORARY STAND IN VALUES)
int INFECTION_TIME = 2;
int get_infection_time()
{
	return INFECTION_TIME;
}

double INFECTIVITY = 0.25;
double get_infect()
{
	return INFECTIVITY;
}

double RECOVERY = 0.15;
double get_recover()
{
	return RECOVERY;
}

//hostiplization
double CONTROL = 0.08;
double Z_FO = 0.25;
double FI_SE = 0.12;
double FIF_SF = 4.0;
double SF_PLUS = 9;

double get_hospilization_age_co(int num)
{
	switch (num)
	{
	case 0:
		return CONTROL * Z_FO;
		break;
	case 1:
		return CONTROL * FI_SE;
		break;
	case 2:
		return CONTROL;
		break;
	case 3:
		return FIF_SF * CONTROL;
		break;
	case 4:
		return SF_PLUS * CONTROL;
		break;
	default:
		return CONTROL;
		break;
	}
	return CONTROL;
}

//child medical

//adult medical

//ethnic group

//Dying
double CONTROL_D = 0.1;
double Z_FO_D = 0.12;
double FI_SE_D = 0.0625;
double FIF_SF_D = 30;
double SF_PLUS_D = 310;

double get_dying_age_co(int num)
{
	switch (num)
	{
	case 0:
		return CONTROL_D * Z_FO_D;
		break;
	case 1:
		return CONTROL_D * FI_SE_D;
		break;
	case 2:
		return CONTROL_D;
		break;
	case 3:
		return FIF_SF_D * CONTROL_D;
		break;
	case 4:
		return SF_PLUS_D * CONTROL_D;
		break;
	default:
		return CONTROL_D;
		break;
	}
	return CONTROL_D;
}