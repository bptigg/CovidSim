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

	RunModel.ScenarioImport(Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies);

	// Make array's
	Actor* actor = new Actor[RunModel.population];
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

	RunModel.CreateModel(Infomation, Population_spread, Population_diversity, child_medical, adult_medical, scenario_param, policies, actor, RunModel.population, primary_school, RunModel.Num_of_Primary_Schools);

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