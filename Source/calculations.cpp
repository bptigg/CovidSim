#include "calculations.h"

double calculations::calc_susceptibility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race)
{
    return 0.5;
}

double calculations::calc_hospital_suceptibility()
{
    return 0.0;
}

double calculations::infection_prob(double odds, Actor::Symptom_Severity modifier)
{
    double modifier_value = get_modifier_value(modifier);
    double prob = (odds / (1 + odds));
    prob = prob * modifier_value;
    return prob;
}

