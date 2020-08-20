#pragma once

#include "Scenario.h"
#include "Setup_info.h"
#include "Objects.h"

namespace Model
{
	void RunModel();
	//void RunModel(); The overload
	void CreateModel();
	void RunRandomModel();
	
	std::string Get_filename();
}