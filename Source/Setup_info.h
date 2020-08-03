#pragma once

#include <map>
#include <tuple>

#include "Matrix.h"

struct World_Infomation
{
	/*Building positions*/
	
	//Schools
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Primary_school;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Secondry_school;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> University;

	//Public services
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Hospital;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> POW;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Restuarant;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Cinema;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Shopping_center;
	std::map<unsigned int, std::tuple<std::pair<int, int >, unsigned int, unsigned int, unsigned int>> Park;

	//Public Transport
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> BusNet;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> TrainNet;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int, int, Matrix<int>>> MetroNet;
	std::map<unsigned int, std::tuple<std::pair<int, int>, unsigned int, unsigned int>> Airport;
};

/* Turns out everything else I need is in scenario.h so no point making more variables for variables that already exist*/