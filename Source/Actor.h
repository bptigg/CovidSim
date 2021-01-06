#pragma once

#include <cstdlib>
#include <algorithm>
#include <functional>

#include <tuple>

#include "Public_Transport_Network.h"
#include "Random.h"

#include "Constants.h"



class Director;
class Public_transport_building;

struct node
{
	std::tuple <int, int, int> location;

	int previous_node_num;
	int node_num;

	int g_cost;
	int h_cost;
	int f_cost;
};

class Actor
{
	friend class Director;
public:

	std::string name;

	unsigned int tile_size = 0;
	unsigned int idle_counts = 0;
	unsigned int task_counts = 0;

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
		airplane, default_vehicle
	};

	enum State
	{
		idle = 0, transit, doing_task, waiting
	};
	
	std::tuple <int, int, int> Destination;
	bool task_dest = false;
	bool A_star_found = false;

	int infection_length = 0;
	bool symptoms = false;
	bool hospital = false;

private:
	double m_infectivity = 0; //This will depend on your sympton severity
	double m_hostiplization_risk = 0; //chance of being hostiplized. Caluclated after being infected
	double m_mortality_risk = 0; //Chance of dying calculated after being infected
	double m_chance_of_recovery = 0; // chan

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

	bool m_a_star_path = false;
	bool m_start_node = false;
	bool m_end_point = false;
	int point_in_path = 0;
	int weight_count = 0;

	int descision = 0;

	std::tuple<int, int, unsigned int> House_coord;
	std::tuple<int, int, unsigned int> Work_coord;

	std::vector<std::tuple<int, int, Vehicle>> a_star_path = {};
	//std::tuple <int, int, int> destination;

private:

	/*All functions are void until they have been written*/
	//void A_star_algorithim(Transport_Net* network, Matrix<int> graph, Matrix<int> tile_matrix);
	Matrix<double> Get_move_matrix(std::pair<unsigned int , unsigned int> destination, bool random);
	
	void Social_distancing();
	int get_distance(std::tuple <int, int, unsigned int> loc_start, std::tuple <int, int, unsigned int> loc_end);

	int get_nearest_node(Transport_Net* network, std::tuple<int, int, int> location);
	double matrix_distance(node& start_node, node& end_node, Matrix<int> tile_matrix);

public:

	void show();

	bool ask_director();

	bool A_star_algorithim(Transport_Net* network, Matrix<int> tile_matrix);
	void random_walk();
	bool weighted_walk(std::pair<unsigned int, unsigned int> location);
	bool go_to_place(std::tuple<int, int, int> destination, Transport_Net* network, Matrix<int> tile_matrix);

	Actor::State state_check();
	void set_state(Actor::State state);
	Actor::Stage stage_check();
	
	Actor::Vehicle Get_Vehicle();
	std::tuple<unsigned int, unsigned int, unsigned int> Get_Location();
	std::tuple<unsigned int, unsigned int, unsigned int> House_Location();
	std::tuple<unsigned int, unsigned int, unsigned int> Work_Location();
	Actor::Age_Catagory Get_age();
	Actor::Location get_location();
	double get_infectivity_risk();
	double get_hospilization_risk();
	double get_mortality_risk();
	Actor::Symptom_Severity get_severity();

	void Age(Age_Catagory age);
	void set_symptom_severity(unsigned int severity);
	void set_infectivity(double infectivity);
	void set_stage(Actor::Stage stage);
	void set_hostpilization_risk(double risk);
	void set_mortality(double risk);
	void set_recovery(double risk);
	void set_work_location(std::tuple<int, int, unsigned int> work);
	void set_home_location(std::tuple<int, int, unsigned int> home);
	void set_location(unsigned int x, unsigned int y, unsigned int tile_num);
	void set_location_state(Actor::Location location_state);

	bool show_symptoms();
	bool go_to_hospital();
	bool recover();
	bool die();
	//bool add_back_to_succept();

};

