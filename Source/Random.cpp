#include "Random.h"

std::vector<unsigned int> Random::Discrete_distribution(std::vector<double>& weights, unsigned int runs)
{
	std::vector<unsigned int> Results;

	Log get_time(Log::LogLevelInfo);
	std::string time = get_time.GetCurrentTime();
	std::seed_seq stime (time.begin(), time.end());
	

	std::discrete_distribution<int> dist(std::begin(weights), std::end(weights));
	std::mt19937 gen;
	gen.seed(stime);

	for (unsigned int i = 0; i < runs; i++)
	{
		unsigned int result = dist(gen);
		Results.push_back(result);
	}

	return Results;
}

