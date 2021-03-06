#pragma once

#include <map>
#include <tuple>

#include "Matrix.h"

#include "Objects.h"

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

struct Tile
{
	~Tile()
	{
		edu_buildings.clear();
		Pub_buildings.clear();
		public_transport.clear();

		Houses.clear();
		Generic_work.clear();

		entity_currently_on_tile.clear();
	}

	uint32_t size = 0;

	std::vector<Education_Buildings*> edu_buildings;
	std::vector<Public_Buildings*> Pub_buildings;
	std::vector<Public_transport_building*> public_transport;

	std::vector<House*> Houses;
	std::vector<Generic_work*> Generic_work;

	std::vector<Actor*> entity_currently_on_tile;

};
