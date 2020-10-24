#pragma once

#include "Actor.h"

namespace calculations
{
	double calc_susceptibility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race);
	double calc_hospital_suceptibility();
}