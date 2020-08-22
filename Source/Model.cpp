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

	Actor* actor = new Actor[RunModel.population];

	Education_Buildings* primary_school = new Education_Buildings[RunModel.Num_of_Primary_Schools];
	Education_Buildings* secondry_school = new Education_Buildings[RunModel.Num_of_Secondry_Schools];
	Education_Buildings* further_education = new Education_Buildings[RunModel.Num_of_Uni];
	
	Public_Buildings* Hospital = new Public_Buildings[RunModel.Num_of_Hospitals];

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