#pragma once

#include <cstdlib>

#include <tuple>
#include "Matrix.h"
#include "Random.h"
//#include "Tasks.h";

class Actor
{
public:
	unsigned int tile_size = 0;
	unsigned int idle_counts = 0;
	unsigned int task_counts = 0;

	//Task* m_task;

	enum Age_Catagory
	{
		zero_to_four = 0, five_to_seventeen, eighteen_to_fortynine, fifty_to_sixtyfour, sixtyfive_plus, default_age_range
	};


	enum Symptom_Severity
	{
		asymptomatic, mildely_symptomatic, full_symptoms, default_severity
	};

	enum Stage
	{
		sucept = 0, infect, rec, Host, dead
	};

	enum Work_risk
	{
		no_added_risk = 0, high_risk
	};

	enum Location
	{
		home = 0, work, public_building, in_transit, outside, unkown
	};

	enum Vehicle
	{
		Bus = 0, Train, Metro_train, airplane, default_vehicle
	};

	enum State
	{
		idle = 0, transit, doing_task
	};

private:
	double m_infectivity = 0; //This will depend on your sympton severity
	double m_host_risk = 0; //chance of being infected
	double m_hostiplization_risk = 0; //chance of being hostiplized. Caluclated after being infected
	double m_mortality_risk = 0; //Chance of dying calculated after being infected

	Age_Catagory m_age_range = default_age_range;
	Symptom_Severity m_Sev = default_severity;
	Stage m_stage = sucept;
	Work_risk m_risk_modifier = no_added_risk; //This is more for social distancing polices than anything else
	Location location = unkown;
	Vehicle m_mode_of_transport = default_vehicle;
	State m_state = idle;

	int m_x = 0;
	int m_y = 0;
	unsigned int m_tilenum = 0;

	unsigned int direction = 0;

	std::tuple<int, int, unsigned int> House_coord;
	std::tuple<int, int, unsigned int> Work_coord;

private:

	/*All functions are void until they have been written*/
	void A_star_algorithim();
	Matrix<double> Get_move_matrix(std::pair<unsigned int , unsigned int> destination, bool random);
	void directional_work();
	
	void Social_distancing();

public:
	Actor();
	~Actor();

	void random_walk();
	bool weighted_walk(std::pair<unsigned int, unsigned int> location);
	void go_to_place(std::tuple<int, int, int> destination);

	Actor::State state_check();
	Actor::Stage stage_check();
	
	void Get_Vehicle();
	std::tuple<unsigned int, unsigned int, unsigned int> Get_Location();
	std::tuple<unsigned int, unsigned int, unsigned int> House_Location();
	std::tuple<unsigned int, unsigned int, unsigned int> Work_Location();
	Actor::Age_Catagory Get_age();
	Actor::Location get_location();
	double get_host_risk();
	Actor::Symptom_Severity get_infectivity_risk();

	void Age(Age_Catagory age);
	void set_symptom_severity(unsigned int severity);
	void set_infectivity();
	void set_stage(Actor::Stage stage);
	void set_hostpilization_risk();
	void set_host_risk(double risk);
	void set_mortality();
	void set_work_location(std::tuple<int, int, unsigned int> work);
	void set_home_location(std::tuple<int, int, unsigned int> home);
	void set_location(unsigned int x, unsigned int y, unsigned int tile_num);
	void set_location_state(Actor::Location location_state);

};