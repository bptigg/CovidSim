#pragma once

#include "Matrix.h"
#include "Public_Transport.h"

struct Transport_Net
{
	std::vector<Public_transport_building*> Bus_Network;
	Matrix<int>* BusNetwork = new Matrix<int>(Bus_Network.size(), Bus_Network.size());

	std::vector<Public_transport_building*> Train_Network;
	Matrix<int>* TrainNetwork = new Matrix<int>(Train_Network.size(), Train_Network.size());

	std::vector<Public_transport_building*> Metro_Network;
	Matrix<int>* MetroNetwork = new Matrix<int>(Metro_Network.size(), Metro_Network.size());

	std::vector<Public_transport_building*> Airports;

	Matrix<int>* TransportNetwork = new Matrix<int>(0, 0);
	std::map<unsigned int, std::pair<std::tuple<unsigned int, unsigned int, unsigned int>, std::vector<Public_transport_building*>>> public_transport_network;
};