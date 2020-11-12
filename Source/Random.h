#pragma once

#include <random>
#include <vector>

#include "Logging API.h"

namespace Random
{
	std::vector<unsigned int> Discrete_distribution(std::vector<unsigned int>& weights, unsigned int runs);
	std::vector<unsigned int> Discrete_distribution(std::vector<double>& weights, unsigned int runs);

	unsigned int random_number(int min, int max, std::vector<unsigned int> used_numbers);
}