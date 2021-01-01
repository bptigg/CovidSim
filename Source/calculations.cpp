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

double calculations::building_infection_modifier(int number_of_infected)
{
    double modifier_value = 1 + (log(number_of_infected) / log(10));
    if (modifier_value >= 2.5)
    {
        modifier_value = 2.5;
    }
    return modifier_value;
}

double calculations::transport_infection_modifier(int number_of_infected)
{
    double modifer_value = 1 + (log(number_of_infected) / log(100));
    if (modifer_value >= 2.5)
    {
        modifer_value = 2.5;
    }
    return modifer_value;
}

double calculations::R_0(int previous, int now)
{
    int new_infected = now - previous;
    return ((double)new_infected / (double)previous);
}

double calculations::rate(int total, int previous, int now)
{
    int new_infected = now - previous;
    return (new_infected / total) * 100000;
}

