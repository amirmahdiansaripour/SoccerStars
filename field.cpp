#include "definitions.hpp"
#include "game_element.hpp"
#include "team.hpp"
#include "field.hpp"

Field::Field(Window* game_table_){
	teams = new vector<Team>(ZERO);
	game_table = game_table_;
	team_turn = ZERO;
	initial_positions_choosed = false;
}

Field::Field(){
	teams = NULL_POINTER;
	game_table = NULL_POINTER;
	team_turn = ZERO;
	initial_positions_choosed = false;
}

Window* Field::get_table(){
	return game_table;
}
void Field::add_team(Team added_team){
	teams->push_back(added_team);
}
void Field::add_ball(Game_element ball_){
	ball = ball_;
}
vector<Team>* Field::get_teams(){
	return teams;
}
Game_element* Field::get_ball(){
	return &ball;
}
void Field::initial(){
	num_of_goals_to_win_the_match = 3;
	num_of_matches = 2;
	Team first_team(FIRST_TEAM_COLOR,this);
	Team second_team(SECOND_TEAM_COLOR,this);
	add_team(first_team);
	add_team(second_team);
	add_ball(Game_element());
	first_team.add_players();
	second_team.add_players();
}
Event Field::get_last_event(){
	return get_table()->poll_for_event();
}

void Field::reset_velocities(){
	get_ball()->change_velocity(Point(ZERO,ZERO));
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		teams->at(ZERO).get_players_of_team()->at(counter).change_velocity(Point(ZERO,ZERO));
		teams->at(ONE).get_players_of_team()->at(counter).change_velocity(Point(ZERO,ZERO));
	}
}

void Field::handle_goal(int winner){
	teams->at(winner).increment_num_of_goals();
	if(teams->at(winner).get_num_of_goals() >= num_of_goals_to_win_the_match){
		teams->at(winner).increment_num_of_won_matches();
		show_state();
		teams->at(winner).reset_goals();
		teams->at(1 - winner).reset_goals();
    }
}
int Field::check_if_any_team_won_the_match(){
	if(teams->at(ZERO).get_num_of_won_matches() > num_of_matches){
		return ZERO;
	}
	if(teams->at(ONE).get_num_of_won_matches() > num_of_matches){
		return ONE;
	}
	return UNDEFINED;
}

int Field::check_if_any_team_won_a_set(){
	if(teams->at(ZERO).get_num_of_goals() >= num_of_goals_to_win_the_match){
		return ZERO;
	}
	else if(teams->at(ONE).get_num_of_goals() >= num_of_goals_to_win_the_match){
		return ONE;
	}
	else{
		return UNDEFINED;
	}
}

bool mouse_is_in_field(Point mouse_position){
	if(mouse_position.x < WIDTH && mouse_position.x > ZERO && mouse_position.y < HEIGHT && mouse_position.y > ZERO){
		return true;
	}
	else{
		return false;
	}
}

bool check_if_clicked(Point player_position,Point mouse_position){
	if(mouse_position.x < player_position.x + DISTANCE_FROM_CENTER + TELORANCE && mouse_position.x > player_position.x-DISTANCE_FROM_CENTER-TELORANCE
			&&mouse_position.y > player_position.y - DISTANCE_FROM_CENTER - TELORANCE && mouse_position.y < player_position.y + DISTANCE_FROM_CENTER + TELORANCE&&
			mouse_is_in_field(mouse_position)){
		return true;
	}
	else{
		return false;
	}
}

float calculate_vector_size(Point begin, Point end){
	return sqrt((begin.x - end.x)*(begin.x - end.x) + (begin.y - end.y)*(begin.y - end.y));
}

bool two_points_are_not_equal(Point first , Point second){
	if(first.x == second.x && first.y == second.y){
		return false;
	}
	else{
		return true;
	}
}


bool check_for_collision(Point first_position, Point second_position, int distance_of_two_centers){
	if(two_points_are_not_equal(first_position,second_position) && calculate_vector_size(first_position,second_position) <= distance_of_two_centers){
		return true;
	}
	else{
		return false; 
	}
}

bool check_wrong_indexes(int counter1,int counter2, int first_team, int second_team){
	if(counter1 == counter2 && first_team == second_team){
		return false;
	}
	else{
		return true;
	}
}

Collision two_player_collision(int first_team , int second_team, vector<Team>* teams){
	int counter1, counter2;
	for(counter1 = ZERO; counter1 < NUM_OF_PLAYERS_IN_A_TEAM; counter1++){
		for(counter2=ZERO; counter2 < NUM_OF_PLAYERS_IN_A_TEAM; counter2++){
			if(check_wrong_indexes(counter1,counter2,first_team,second_team) 
				&& check_for_collision(teams->at(first_team).get_players_of_team()->at(counter1).get_position_of_player(),
				teams->at(second_team).get_players_of_team()->at(counter2).get_position_of_player(),PLAYER_PIECE_LENGTH)){
				Collision between_players;
				between_players.first_player = &(teams->at(first_team).get_players_of_team()->at(counter1));
				between_players.second_player = &(teams->at(second_team).get_players_of_team()->at(counter2));
				return between_players;
			}
		}
	}
	Collision nothing_happend;
	nothing_happend.first_player = NULL_POINTER;
	return nothing_happend;
 }

Collision palyer_ball_collision(Team* team, Game_element* ball){
	int counter;
	for(counter = ZERO; counter < team->get_players_of_team()->size(); counter++){
		if(check_for_collision(team->get_players_of_team()->at(counter).get_position_of_player()
			,ball->get_position_of_player(),DISTANCE_FROM_CENTER + LESS_TELORANCE)){
			Collision between_player_and_ball;
			between_player_and_ball.first_player = &(team->get_players_of_team()->at(counter));
			between_player_and_ball.second_player = ball;
			return between_player_and_ball;
		}
	}
	Collision nothing_happend;
	nothing_happend.first_player = NULL_POINTER;
	return nothing_happend;
}

vector<Collision>* Field::get_collisions(){
	vector<Collision>* Collisions = new vector<Collision>;
	Collision first_case = two_player_collision(ZERO,ZERO,teams);
	if(first_case.first_player != NULL_POINTER){
		Collisions->push_back(first_case);
	}
	
	Collision second_case = two_player_collision(ZERO,ONE,teams);
	if(second_case.first_player != NULL_POINTER){
		Collisions->push_back(second_case);
	}
	
	Collision third_case = two_player_collision(ONE,ONE,teams);
	if(third_case.first_player != NULL_POINTER){
		Collisions->push_back(third_case);
	}
	
	Collision forth_case = palyer_ball_collision(&(teams->at(ZERO)), &ball);
	if(forth_case.first_player != NULL_POINTER){
		Collisions->push_back(forth_case);
	}
	
	Collision fifth_case = palyer_ball_collision(&teams->at(ONE),&ball);
	if(fifth_case.first_player != NULL_POINTER){
		Collisions->push_back(fifth_case);
	}
	return Collisions;
}

Point calculate_velocities_after_collision(Game_element* first_player,Game_element* second_player){
	Point position_diff = first_player->get_position_of_player() - second_player->get_position_of_player();
	Point velocity_diff = first_player->get_velocity() - second_player->get_velocity();
	float dot_product = velocity_diff.x * position_diff.x + velocity_diff.y * position_diff.y;
	float position_norm = calculate_vector_size(first_player->get_position_of_player(),second_player->get_position_of_player());
	position_norm = position_norm*position_norm;
	float coefficient = (2*(second_player->get_mass_of_player()) / (first_player->get_mass_of_player() + second_player->get_mass_of_player()));
	coefficient = coefficient * (dot_product / position_norm);
	float x = first_player->get_velocity().x - coefficient*(position_diff.x);
	float y = first_player->get_velocity().y - coefficient*(position_diff.y);
	return Point(x,y);
}

void Field::change_velocities_when_collision(vector<Collision>* Collisions){
	int counter;
	for(counter = ZERO; counter < Collisions->size(); counter++){
		if(Collisions->at(counter).first_player == NULL_POINTER){
			continue;
		}
		else if(Collisions->at(counter).first_player != NULL_POINTER && Collisions->at(counter).second_player != NULL_POINTER){
			Point changed_v_for_first_player = calculate_velocities_after_collision(Collisions->at(counter).first_player,Collisions->at(counter).second_player);
			Point changed_v_for_second_player = calculate_velocities_after_collision(Collisions->at(counter).second_player,Collisions->at(counter).first_player);
			Collisions->at(counter).first_player->change_velocity(changed_v_for_first_player);
			Collisions->at(counter).second_player->change_velocity(changed_v_for_second_player);
		}
	}
}

void Field::change_positions_after_collision(){
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		teams->at(ZERO).get_players_of_team()->at(counter).change_position_of_player();
	}
	for(counter=ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		teams->at(ONE).get_players_of_team()->at(counter).change_position_of_player();
	}
	ball.change_position_of_player();
}

void Field::change_turn(int beginner_team){
	if(beginner_team != UNDEFINED){
        team_turn = beginner_team;
    }	
    else{
        if(team_turn == ZERO){
        	team_turn = ONE;
        }
        else{
        	team_turn = ZERO;
        }
    }  
}

Game_element* Field:: choose_player_to_move(){
	Event current_event = get_last_event();
	vector<Game_element>* players = new vector<Game_element>;
	players = teams->at(team_turn).get_players_of_team();
	if(current_event.get_type() == Event::EventType::LCLICK){
		int counter;
		Point mouse_position = current_event.get_mouse_position();
		for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
			Point player_position =  players->at(counter).get_position_of_player();
			if(check_if_clicked(player_position,mouse_position)){
				return &(players->at(counter));
			}
		}
	}
	return NULL_POINTER;
}

int check_goal_line(Point ball_position){
	if(ball_position.x >= MAX_LIMIT_X + TELORANCE- PLAYER_PIECE_LENGTH &&
	ball_position.y >= POST1_POSITION &&  ball_position.y <= POST2_POSITION){
		return ONE;
	}
	else if(ball_position.x <= MIN_LIMIT_X + LESS_TELORANCE + PLAYER_PIECE_LENGTH && 
	ball_position.y >= POST1_POSITION &&  ball_position.y <= POST2_POSITION){
		return ZERO;
	}
	else{
		return UNDEFINED;
	}
}

int Field::check_if_any_team_scored(){
	Point position = ball.get_position_of_player();
	int result = check_goal_line(position);
	return result;
}

void Field::print_message(string message, const RGB color){
	game_table->fill_rect(Rectangle(Point(GOAL_PICTURE_X,GOAL_PICTURE_Y-GOAL_PICTURE_WIDTH),GOAL_PICTURE_WIDTH,GOAL_PICTURE_HEIGHT),color);
	game_table->show_text(message,Point(GOAL_PICTURE_X + TELORANCE,TELORANCE),BLACK,FONT,20);
}

void Field::reset_locations(){
	ball.reset_locations();
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		teams->at(ZERO).get_players_of_team()->at(counter).reset_locations();
		teams->at(ONE).get_players_of_team()->at(counter).reset_locations();
	}
}

bool Field::get_initial_positions(){
	return initial_positions_choosed;
}

void Field::all_have_initial_pos(){
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		if(teams->at(ZERO).get_players_of_team()->at(counter).get_first_position() == ZERO){
			return ;
		}
	}
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		if(teams->at(ONE).get_players_of_team()->at(counter).get_first_position() == ZERO){
			return ;
		}
	}
	initial_positions_choosed = true;
	return;
}

bool team_in_its_half(Point unsuitable_place, int index){
	if(index == ZERO && unsuitable_place.x < WIDTH/2){
        return false;
    }
    else if(index == ONE && unsuitable_place.x > WIDTH/2){
        return false;
    }
    return true;
}


Point Field::choose_first_positions(Point initial_pos,int index){
	all_have_initial_pos();
	vector<Game_element>* players_in_team = new vector<Game_element>;
	players_in_team = teams->at(index).get_players_of_team();
	int counter;
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM ; counter++){
		if(players_in_team->at(counter).get_first_position() == ZERO){
			Event current_event = get_last_event();
			if(current_event.get_type() == Event::EventType::LCLICK && mouse_is_in_field(current_event.get_mouse_position())
			 && team_in_its_half(current_event.get_mouse_position(), index)){
				players_in_team->at(counter).assign_first_position(current_event.get_mouse_position());
				initial_pos = current_event.get_mouse_position();
				break;
			}
			else if(current_event.get_type() == Event::EventType::MMOTION){
				players_in_team->at(counter).assign_instant_position(current_event.get_mouse_position());
				initial_pos = current_event.get_mouse_position();
				break;
			}
			else{
				players_in_team->at(counter).assign_instant_position(initial_pos);
				break;
			}
		}
	}
	show_state();
	return initial_pos;
}

void Field::show_turn(string turn, int current_turn, Point P1, Point P2,const RGB team_color){
	game_table->show_text(turn, P2, BLACK, FONT, 20);
	if(initial_positions_choosed && current_turn == team_turn){
		game_table->fill_circle(P1 , TELORANCE / 2, team_color);
    }
}

void Field::show_num_of_goals(Point P1, Point P2, Point P3, int index){
	if(!teams->at(ZERO).players_have_initial_locations() && index == ZERO){
		game_table->show_text("Place 5", P1, GREEN, FONT, 30);
		game_table->show_text("players", P2, GREEN, FONT, 30);
		game_table->show_text("(right)", P3, GREEN, FONT, 30);
	
	}
	else if(teams->at(ZERO).players_have_initial_locations() && 
	!teams->at(ONE).players_have_initial_locations() && index == ONE){
		game_table->show_text("Place 5", P1, RED, FONT, 30);
		game_table->show_text("players", P2, RED, FONT, 30);
		game_table->show_text("(left)", P3, RED, FONT, 30);
	}
	else if(teams->at(ZERO).players_have_initial_locations() && 
			teams->at(ONE).players_have_initial_locations()){
		game_table->show_text(to_string(teams->at(index).get_num_of_goals()), P1, BLACK, FONT, 100);
	}
}

void Field::handle_delay(int goal_scored, int won_set, int won_match){
	if(won_set != UNDEFINED){
   	 	delay(2*LONG_DELAY);
	}
	if(goal_scored != UNDEFINED){
   	 	delay(LONG_DELAY);
	}
	else if(won_match != UNDEFINED){
   	 	delay(2*LONG_DELAY);
	}
	else{
		delay(LESS_DELAY/2);
	}
}

void Field::print_turn_or_match_finished(int result,string first_string,string second_string){
	if(result==ZERO){
    	game_table->fill_rect(Rectangle(Point(GOAL_PICTURE_X,GOAL_PICTURE_Y-GOAL_PICTURE_WIDTH),GOAL_PICTURE_WIDTH,GOAL_PICTURE_HEIGHT),GREEN);
		game_table->show_text(first_string,Point(GOAL_PICTURE_X + TELORANCE,TELORANCE),BLACK,FONT,20);
    }
    else if(result==ONE){
    	game_table->fill_rect(Rectangle(Point(GOAL_PICTURE_X,GOAL_PICTURE_Y-GOAL_PICTURE_WIDTH),GOAL_PICTURE_WIDTH,GOAL_PICTURE_HEIGHT),RED);
		game_table->show_text(second_string,Point(GOAL_PICTURE_X + TELORANCE,TELORANCE),BLACK,FONT,20);
    }
}

void Field::show_state(){
    int counter;
    Rectangle score_table(WIDTH ,ZERO, LENGTH_OF_SCORE_TABLE, HEIGHT);
    Rectangle table(X_OF_SCORE_TABLE, HEIGHT / 4, LENGTH_OF_SCORE_TABLE/2, HEIGHT / 2);
    game_table->fill_rect(score_table, BLUE);
    game_table->fill_rect(table, WHITE);

	show_turn(GREEN_TEAM_TURN, ZERO, Point(X_OF_SCORE_TABLE, HEIGHT / 4 + 2 * TELORANCE), Point(X_OF_SCORE_TABLE + 2 * TELORANCE, HEIGHT / 4), GREEN);
	show_turn(RED_TEAM_TURN, ONE, Point(X_OF_SCORE_TABLE, HEIGHT / 2 + 2 * TELORANCE), Point(X_OF_SCORE_TABLE + 2 * TELORANCE, HEIGHT / 2 + TELORANCE), RED);
	
	show_num_of_goals(Point(X_OF_SCORE_TABLE, HEIGHT / 4 + TELORANCE), Point(X_OF_SCORE_TABLE, HEIGHT / 4 + TELORANCE + 30), Point(X_OF_SCORE_TABLE, HEIGHT / 4 + TELORANCE + 60), ZERO);
	show_num_of_goals(Point(X_OF_SCORE_TABLE, HEIGHT / 2 + 2 * TELORANCE), Point(X_OF_SCORE_TABLE, HEIGHT / 2 + 2 * TELORANCE + 30), Point(X_OF_SCORE_TABLE, HEIGHT / 2 + 2 * TELORANCE + 60), ONE);

	vector<Game_element> temp_players = *((teams->at(ZERO)).get_players_of_team());
    game_table->draw_img(FIELD_PICTURE, Rectangle(ZERO, ZERO, WIDTH, HEIGHT));
    for(counter = ZERO; counter<temp_players.size(); counter++){
    	if(temp_players[counter].get_first_position() != false){
    		game_table->draw_img(FIRST_TEAM_PICTURE,Rectangle((temp_players[counter].get_position_of_player()).x,
                                                 (temp_players[counter].get_position_of_player()).y,PLAYER_PIECE_LENGTH,PLAYER_PIECE_LENGTH));
    	}
    }
	temp_players = *((teams->at(ONE)).get_players_of_team());
    for(counter = ZERO; counter<temp_players.size(); counter++){
    	if(temp_players[counter].get_first_position() != false){
    		game_table->draw_img(SECOND_TEAM_PICTURE,Rectangle((temp_players[counter].get_position_of_player()).x,
                                                 (temp_players[counter].get_position_of_player()).y,PLAYER_PIECE_LENGTH,PLAYER_PIECE_LENGTH));
    	}	
    }
    int goal_scored = check_if_any_team_scored();
    if(goal_scored == UNDEFINED){
    	Game_element instant_of_ball = *(get_ball());
    	game_table->draw_img(BALL_PICTURE,Rectangle(instant_of_ball.get_position_of_player().x,instant_of_ball.get_position_of_player().y,2*LESS_TELORANCE,2*LESS_TELORANCE));
    }
    else if(goal_scored == ZERO || goal_scored == ONE){
    	game_table->draw_img(GOAL_PICTURE,Rectangle(Point(GOAL_PICTURE_X,GOAL_PICTURE_Y),GOAL_PICTURE_WIDTH,GOAL_PICTURE_HEIGHT));
    }
    int won_set = check_if_any_team_won_a_set();
    
	if(won_set == ZERO){
		print_message(FIRST_TEAM_WON_THE_SET, GREEN);
	}
	else if(won_set == ONE){
		print_message(SECOND_TEAM_WON_THE_SET, RED);
	}

	int won_match = check_if_any_team_won_the_match();
    string first_team_won = FIRST_TEAM_WON_THE_MATCH  + to_string(num_of_matches)+ "matches";
    string second_team_won = SECOND_TEAM_WON_THE_MATCH  + to_string(num_of_matches)+ "matches";
	if(won_match == ZERO){
		print_message(first_team_won,GREEN);
	}
	else if(won_match == ONE){
		print_message(second_team_won, RED);
	}
	game_table->update_screen();
	handle_delay(goal_scored, won_set, won_match);
}

Point Field::left_click_is_released(){
	while(true){
		Event current_event = get_last_event();
		if(current_event.get_type() == Event::EventType::LRELEASE){
			return (current_event.get_mouse_position());
		}
		show_state();
	}
}

bool Field:: elements_are_inert(){
	int counter;
	vector<Game_element> first_team_players = *(teams->at(ZERO).get_players_of_team());
	if(two_points_are_not_equal(ball.get_velocity(), Point(ZERO,ZERO))){
		return false;
	}
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		if(two_points_are_not_equal(first_team_players[counter].get_velocity(),Point(ZERO,ZERO))){
			return false;
		}
	}
	vector<Game_element> second_team_players = *(teams->at(ONE).get_players_of_team());
	for(counter = ZERO; counter < NUM_OF_PLAYERS_IN_A_TEAM; counter++){
		if(two_points_are_not_equal(second_team_players[counter].get_velocity(),Point(ZERO,ZERO))){
			return false;
		}
	}
	return true;
}


