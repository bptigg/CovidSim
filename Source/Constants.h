#pragma once
#include <vector>
#include <tuple>

uint32_t get_max_family_size();
uint32_t get_num_of_households_per_block();
uint32_t get_num_of_offices_per_block();
uint32_t get_max_office_size();

double get_percentage_asymptomatic();
double get_percentage_mild();

uint32_t get_infection_distance();

uint32_t get_starting_infected();

double get_modifier_value(int value);

uint32_t get_max_idle_time();
uint32_t get_min_idle_time();
uint32_t get_counts_per_day();

double get_time_modifier();



/*Everything in this headfile will be a constant variable will actually make this file at somepoint just not now*/