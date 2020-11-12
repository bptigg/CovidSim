#pragma once

#include "Actor.h"
#include "Constants.h"

namespace calculations
{
	double calc_susceptibility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race);
	double calc_hospital_suceptibility();

	double infection_prob(double odds, Actor::Symptom_Severity modifier);
}

