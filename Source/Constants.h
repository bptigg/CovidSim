#pragma once
#include <vector>
#include <string>
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

unsigned int get_max_walk();

double get_chance();

uint32_t get_min_period();
uint32_t get_max_period();
uint32_t get_day_length();
uint32_t get_latent_time();

std::vector<std::string> get_names();

int get_infection_time();
double get_infect();
double get_recover();
double get_hospilization_age_co(int num);
double get_dying_age_co(int num);
