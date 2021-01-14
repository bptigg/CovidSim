#include "Random.h"

std::vector<unsigned int> Random::Discrete_distribution(std::vector<unsigned int>& weights, unsigned int runs)
{
	std::vector<unsigned int> Results;

	Log get_time(Log::LogLevelInfo);
	std::string time = get_time.GetCurrentTime();
	std::seed_seq stime (time.begin(), time.end());
	
	for (auto num : weights)
	{
		if (num < 0 || num > 100)
		{
			weights.clear();
			for (int i = 0; i < weights.size(); i++)
			{
				weights.push_back(25);
			}
			break;
		}
	}

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

std::vector<unsigned int> Random::Discrete_distribution(std::vector<double>& weights, unsigned int runs)
{
	std::vector<unsigned int> Results;

	Log get_time(Log::LogLevelInfo);
	std::string time = get_time.GetCurrentTime();
	std::seed_seq stime(time.begin(), time.end());


	int size = weights.size();
	for (auto num : weights)
	{
		if (num < 0 || num > 1)
		{
			weights.clear();
			for (int i = 0; i < size; i++)
			{
				weights.push_back((1/size));
			}
			break;
		}
	}

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

unsigned int Random::random_number(int min, int max, std::vector<unsigned int> used_numbers)
{
	std::default_random_engine gen;
	std::uniform_int_distribution<int> random(min, max);
	bool number_found = false;

	Log get_time(Log::LogLevelInfo);
	std::string time = get_time.GetCurrentTime();
	std::seed_seq stime(time.begin(), time.end());
	gen.seed(stime);

	while (number_found == false)
	{
		unsigned int random_number = random(gen);
		if (std::find(used_numbers.begin(), used_numbers.end(), random_number) == used_numbers.end())
		{
			number_found = true;
			return random_number;
		}
	}
	return 0;
}
