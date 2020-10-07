#pragma once

#include "Matrix.h"
#include "Public_Transport.h"

struct Transport_Net
{
	std::vector<Public_transport_building*> Bus_Network;
	Matrix<int>* BusNetwork = new Matrix<int>(sizeof(Bus_Network), sizeof(Bus_Network));

	std::vector<Public_transport_building*> Train_Network;
	Matrix<int>* TrainNetwork = new Matrix<int>(sizeof(Train_Network), sizeof(Train_Network));

	std::vector<Public_transport_building*> Metro_Network;
	Matrix<int>* MetroNetwork = new Matrix<int>(sizeof(MetroNetwork), sizeof(MetroNetwork));

	std::vector<Public_transport_building*> Airports;
};