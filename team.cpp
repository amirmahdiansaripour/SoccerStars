#include "definitions.hpp"
#include "game_element.hpp"
#include "team.hpp"

Team::Team(){
	match_field = NULL_POINTER;
}
Team::Team(string color,Field* field){
	team_color = color;
	match_field = field;
	players = new vector<Game_element>(ZERO);
	num_of_goals = ZERO;
	num_of_matches_won = ZERO;
}

int Team::get_num_of_won_matches(){
	return num_of_matches_won;
}

void Team::increment_num_of_won_matches(){
	num_of_matches_won++;
}

void Team::reset_goals(){
	num_of_goals = ZERO;
}

Field* Team::get_match_field(){
	return match_field;
}
vector<Game_element>* Team::get_players_of_team(){
	return players;
}

int Team::get_num_of_goals(){
	return num_of_goals;
}

string Team::get_team_color(){
	return team_color;
}
void Team::add_player_to_team(Game_element new_player){
	players->push_back(new_player);
}
void Team::add_players(){
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		Game_element new_player(Point(ZERO,ZERO),this,counter);
		add_player_to_team(new_player);
	}
}

bool Team::players_have_initial_locations(){
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		if(!players->at(counter).get_first_position()){
			return false;
		}
	}
	return true;
}

void Team:: increment_num_of_goals(){
	num_of_goals++;
}
