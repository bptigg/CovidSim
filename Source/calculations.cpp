#include "calculations.h"

double calculations::calc_susceptibility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race)
{
    double age_co = 0;
    double medical_co = 0;
    double race_co = 0;

    if (age_range != 2)
    {
        age_co = get_hospilization_age_co((int)age_range);
    }
    if (medical != 9)
    {
        medical_co = get_medical();
    }
    if (race != 0)
    {
        race_co = get_ethnicity_co(race); //temp
    }

    double prob = (exp(age_co + medical_co + race_co) * (exp(get_hospilization_age_co(2)) / (1 + exp(get_hospilization_age_co(2)))));
    if (prob > 1)
    {
        prob = 1;
    }
    
    return prob;
}

double calculations::calc_mortaility(Actor::Age_Catagory age_range, unsigned int medical, unsigned int race)
{
    return (get_dying_age_co(age_range)  * (get_dying_age_co(2)/ 1 + get_dying_age_co(2)));
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

