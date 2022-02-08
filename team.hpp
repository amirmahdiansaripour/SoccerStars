#ifndef TEAM_H
#define TEAM_H "TEAM_H"

class Field;
class Game_element;

class Team{
public:
	Team();

	Team(string,Field*);

	Field* get_match_field();

	vector<Game_element>* get_players_of_team();

	string get_team_color();

	int get_num_of_goals();

	int get_num_of_won_matches();

	void add_player_to_team(Game_element);

	void add_players();

	void first_position_of_players();

	void increment_num_of_goals();

	bool players_have_initial_locations();

	void increment_num_of_won_matches();

	void reset_goals();

private:
	vector<Game_element>* players;
	string team_color;
	Field* match_field;
	int num_of_goals;
	int num_of_matches_won;
};

#endif