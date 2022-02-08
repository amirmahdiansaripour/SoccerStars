#include "definitions.hpp"
#include "game_element.hpp"
#include "team.hpp"
#include "field.hpp"
#include "controller.hpp"

int main(){
	Window game_table((WIDTH + LENGTH_OF_SCORE_TABLE), HEIGHT, GAMETABLE);
    Field match_field(&game_table);
    Controller game_controller(match_field);
    game_controller.initial_screen(game_table);
    game_controller.initial_field();
    game_controller.handle_game();
}

