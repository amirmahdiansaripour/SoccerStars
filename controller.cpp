#include "definitions.hpp"
#include "game_element.hpp"
#include "team.hpp"
#include "field.hpp"
#include "controller.hpp"

Controller::Controller(Field& F){
    match_field = F;
}

void Controller::initial_screen(Window& game_table){
    int time = ZERO;
    while(time != 30 * LESS_DELAY){
        game_table.draw_img(FIFA_PICTURE, Rectangle(ZERO,ZERO,WIDTH + LENGTH_OF_SCORE_TABLE,HEIGHT));
        game_table.update_screen();
        delay(LESS_DELAY);
        time++;
    }
}

void Controller::initial_field(){
    Point initial_position(600 ,300);
    match_field.initial();
    while(!match_field.get_initial_positions()){
        if(!match_field.get_teams()->at(ZERO).players_have_initial_locations()){
            initial_position = match_field.choose_first_positions(initial_position,ZERO);
        }
        else{
            initial_position = match_field.choose_first_positions(initial_position,ONE);
        }
    }
}

void Controller::team_scored(int index){
    match_field.handle_goal(index);
}

void Controller::handle_collisions(){
    vector<Collision>* collisions =  new vector<Collision>(ZERO);
    collisions = match_field.get_collisions();
    if(collisions->size() != ZERO){
        match_field.change_velocities_when_collision(collisions);
    }
    match_field.change_positions_after_collision();
    match_field.show_state();
}

int Controller::handle_motion(){
    int index_of_beginner_team = UNDEFINED;
    while(ONE){	
        if(match_field.elements_are_inert()){
            break;
        }
        handle_collisions();
        int result = match_field.check_if_any_team_scored();
        if(result != UNDEFINED){
            if(result == ONE){
                index_of_beginner_team = ZERO;
                team_scored(ONE);
            }
            else if(result == ZERO){
                index_of_beginner_team = ONE;
                team_scored(ZERO);
            }
            match_field.reset_velocities();
            match_field.reset_locations();
            break;
        }
        delay(LESS_DELAY);
    }
    return index_of_beginner_team;
}

void Controller::handle_game(){
    while (ONE){
        if(match_field.check_if_any_team_won_the_match() != UNDEFINED){
            delay(LONG_DELAY);
            break;
        }
    	Game_element* choosen_player = match_field.choose_player_to_move();
    	if(choosen_player != NULL_POINTER){
    		Point second_position = match_field.left_click_is_released();
    		choosen_player->calculate_velocity(second_position);
            int index_of_beginner_team = handle_motion();
            match_field.change_turn(index_of_beginner_team);
    	}
    	else{
            match_field.show_state();
    		delay(LESS_DELAY/2);
    	}
	}
    match_field.get_table()->clear();
}