#pragma once

#include <random>
#include <vector>

#include "Logging API.h"

namespace Random
{
	std::vector<unsigned int> Discrete_distribution(std::vector<unsigned int>& weights, unsigned int runs);
	std::vector<unsigned int> Discrete_distribution(std::vector<double>& weights, unsigned int runs);
}