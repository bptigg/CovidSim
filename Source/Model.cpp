#include "Model.h"

void Model::CreateModel()
{
	Scenario CreateModel;
	CreateModel.ScenarioEditor();
}

void Model::RunModel()
{
	Scenario RunModel(Get_filename());
	World_Infomation Infomation;
	Scenario::Population_Pyramid Population_spread;
	Scenario::Population_race_data Population_diversity;
	Scenario::Medical_data child_medical;
	Scenario::Medical_data adult_medical;
	Scenario::Scenario_Parameters scenario_param;
	Scenario::Social_Distance_poll policies;

	if (RunModel.ScenarioImport(Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies) == true)
	{
		// Make array's
		Actor* actor = new Actor[RunModel.population];
		Tile* tiles = new Tile[RunModel.Num_Of_Tiles];
		Education_Buildings* primary_school = new Education_Buildings[RunModel.Num_of_Primary_Schools];
		Education_Buildings* secondry_school = new Education_Buildings[RunModel.Num_of_Secondry_Schools];
		Education_Buildings* further_education = new Education_Buildings[RunModel.Num_of_Uni];

		Public_Buildings* Hospital = new Public_Buildings[RunModel.Num_of_Hospitals];
		Public_Buildings* POW = new Public_Buildings[RunModel.Num_of_POWs];
		Public_Buildings* Restuarant = new Public_Buildings[RunModel.Num_of_Restuarants];
		Public_Buildings* Cinema = new Public_Buildings[RunModel.Num_of_Cinemas];
		Public_Buildings* Shopping_center = new Public_Buildings[RunModel.Num_of_Shopping_Centers];
		Public_Buildings* Parks = new Public_Buildings[RunModel.Num_of_Parks];

		Public_transport_building* Bus = new Public_transport_building[RunModel.Num_Bus_Stops];
		Public_transport_building* Train = new Public_transport_building[RunModel.Num_Train_stations];
		Public_transport_building* Airport = new Public_transport_building[RunModel.Num_airports];
		Public_transport_building* Metro = new Public_transport_building[RunModel.Num_metro_stations];

		Transport_Net* transport = new Transport_Net;

		std::vector<std::vector<Actor*>> family_groups = {};
		std::vector<House*> houses = {};
		std::vector<Generic_work*> work_places = {};

		RunModel.CreateModel(tiles, Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies, actor, RunModel.population, primary_school, RunModel.Num_of_Primary_Schools, secondry_school, RunModel.Num_of_Secondry_Schools, further_education, RunModel.Num_of_Uni, Hospital, RunModel.Num_of_Hospitals, POW, RunModel.Num_of_POWs, Restuarant, RunModel.Num_of_Restuarants, Cinema, RunModel.Num_of_Cinemas, Shopping_center, RunModel.Num_of_Shopping_Centers, Parks, RunModel.Num_of_Parks, Bus, RunModel.Num_Bus_Stops, Train, RunModel.Num_Train_stations, Airport, RunModel.Num_airports, Metro, RunModel.Num_metro_stations, *transport, family_groups, houses, work_places);
	}
	std::cin.get();
}

void Model::RunRandomModel()
{
	
}

std::string Model::Get_filename()
{
	std::string filename;

	std::cout << "Scenario filename: ";
	std::cin >> filename;
	return filename;
}