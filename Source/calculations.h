#pragma once

#include<cmath>

#include "Actor.h"


namespace calculations
{
	double calc_susceptibility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race);
	double calc_hospital_suceptibility();

	double infection_prob(double odds, Actor::Symptom_Severity modifier);
	double building_infection_modifier(int number_of_infected);
	double transport_infection_modifier(int number_of_infected);

	double R_0(int previous, int now);
	double rate(int total, int previous, int now);
}

