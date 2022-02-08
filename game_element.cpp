#include "definitions.hpp"
#include "team.hpp"
#include "game_element.hpp"

bool Game_element::sign_changed(float instant, float y){
	if(instant * y < ZERO){
		return true;
	}
	if(instant == ZERO){
		return true;
	}
	else{
		return false;
	}
}

Point Game_element::calculate_phisycal_position(float velocity , float position){
    float instant_of_v ;

    if(velocity > ZERO){
    	instant_of_v = velocity - FRICTION_EFFECT;
    }

    else if(velocity < ZERO){
		instant_of_v = velocity + FRICTION_EFFECT;
	}

    else{
		instant_of_v = velocity;
	}

    if(sign_changed(instant_of_v,velocity)){
		velocity = ZERO;
	}

    else{
		velocity = instant_of_v;
	}

    if(velocity > ZERO){
        position = -(FRICTION_EFFECT/2) +velocity+ position;
    }

    else if(velocity < ZERO){
		position = (FRICTION_EFFECT/2) +velocity + position;
	}

   	return Point(velocity,position);
}

bool Game_element::dont_reflect(Point position){
    if(position.y >= POST1_POSITION && position.y <= POST2_POSITION && (position.x >= MAX_LIMIT_X || position.x <= MIN_LIMIT_X)){
        return true;
    }
    else{
        return false;
    }
}

Point Game_element::reflect_if_need(Point position, int high_limit, int low_limit){
    if(get_mass_of_player() == ONE && dont_reflect(position)){
        return position;
    }
	if(position.y < low_limit){
		position.y = low_limit + abs(low_limit - position.y);
		position.x = -1 * position.x;
	}
	else if(position.y > high_limit){
		position.y = high_limit - abs(high_limit - position.y);
		position.x = -1 * position.x;
	}
	return position;
}

Game_element:: Game_element(){
	position = Point(WIDTH/2 ,HEIGHT/2 -LESS_TELORANCE);
	team = NULL_POINTER;
	velocity = Point(ZERO,ZERO);
	mass = ONE;
    first_position_choosed = true;
    first_position = position;
	player_shirt_num = UNDEFINED;
}

Game_element::Game_element(Point pos, Team*team_playing_in, int num){
	position = pos;
	mass = MASS_OF_EACH_PLAYER;
	team = team_playing_in;
	velocity = Point(ZERO,ZERO);
	first_position_choosed = false;
	player_shirt_num = num;
}

void Game_element::reset_locations(){
    position = first_position;
}

Team* Game_element::get_team_of_player(){
    return team;
}

float Game_element::get_mass_of_player(){
    return mass;
}

Point Game_element::get_position_of_player(){
    return position;
}

Point Game_element::get_velocity(){
    return velocity;
}

void Game_element::change_velocity(Point new_velocity){
    velocity = new_velocity;
}

int Game_element::get_shirt_num(){
    return player_shirt_num;
}

void Game_element:: change_position_of_player(){
	Point x_result = calculate_phisycal_position(velocity.x, position.x);
	x_result = reflect_if_need(x_result, MAX_LIMIT_X, MIN_LIMIT_X);
	Point y_result = calculate_phisycal_position(velocity.y,position.y);
	y_result = reflect_if_need(y_result, MAX_LIMIT_Y, MIN_LIMIT_Y);
	velocity.x = x_result.x;
	position.x = x_result.y;
	velocity.y = y_result.x;
	position.y = y_result.y;
}

void Game_element::calculate_velocity(Point second_position){
	Point player_position = get_position_of_player();
	Point d(second_position.x - player_position.x , second_position.y - player_position.y);
	float norm = sqrt(((d.x)*(d.x)) + ((d.y)*(d.y)));
	float vx,vy;
	if(norm < THROW_RADIUS){
		vx = ((MAX_INITIAL_SPEED/THROW_RADIUS)) * (d.x);
		vy = ((MAX_INITIAL_SPEED/THROW_RADIUS)) * (d.y);
	}
	else{
		vx = ((MAX_INITIAL_SPEED/norm)) * (d.x);
		vy = ((MAX_INITIAL_SPEED/norm)) * (d.y);
	}
	change_velocity(Point(vx,vy));
}


Point Game_element::put_in_suitable_place(Point unsuitable_place){
    if(unsuitable_place.y > MAX_LIMIT_Y){
        unsuitable_place.y = MAX_LIMIT_Y;
    }
    if(unsuitable_place.x < MIN_LIMIT_X){
        unsuitable_place.x = MIN_LIMIT_X;
    }
    else if(unsuitable_place.x > MAX_LIMIT_X){
        unsuitable_place.x = MAX_LIMIT_X;
    }
    return unsuitable_place;
}



void Game_element::assign_first_position(Point initial_position){
    initial_position = put_in_suitable_place(initial_position);
    first_position = initial_position;
    position = initial_position;
    first_position_choosed = true;
}

bool Game_element::get_first_position(){
    return first_position_choosed;
}

void Game_element:: assign_instant_position(Point instant_position){
    position = instant_position;
}
