#ifndef DEF_H
#define DEF_H "DEF_H"

#define WIDTH 1000
#define HEIGHT 600
#define ZERO 0
#define ONE 1
#define NOTHING ""
#define LESS_TELORANCE 10
#define NULL_POINTER NULL
#define GAMETABLE "Game Table"
#define FIELD_PICTURE "field.jpg"
#define FIRST_TEAM_PICTURE "Player1.png"
#define SECOND_TEAM_PICTURE "Player2.png"
#define NUM_OF_PLAYERS_IN_A_TEAM 5
#define NUM_OF_GOALS_TO_WIN_THE_SET 3
#define NUM_OF_SETS_TO_WIN_THE_GAME 2
#define DISTANCE_FROM_CENTER 15
#define PLAYER_PIECE_LENGTH 30
#define FIRST_TEAM_COLOR "GREEN"
#define SECOND_TEAM_COLOR "RED"
#define BALL_PICTURE "ball.png"
#define GOAL_PICTURE "goal.png"
#define GOAL_PICTURE_X 319
#define GOAL_PICTURE_Y 212
#define FONT "FreeSans.ttf"
#define GOAL_PICTURE_WIDTH 310
#define GOAL_PICTURE_HEIGHT 182
#define TELORANCE 20
#define FIFA_PICTURE "fifa.jpg"
#define THROW_RADIUS 50
#define UNDEFINED -1
#define MAX_INITIAL_SPEED 50
#define MASS_OF_EACH_PLAYER 2
#define MASS_OF_BALL 1
#define FRICTION_EFFECT 5
#define LONG_DELAY 1000
#define LESS_DELAY 10
#define GREEN_TEAM_TURN "Green team:"
#define RED_TEAM_TURN "Red team:"
#define POST1_POSITION 207
#define POST2_POSITION 399
#define MAX_LIMIT_X 965
#define MAX_LIMIT_Y 565
#define MIN_LIMIT_X 5
#define SET_RED_LOCATIONS "Place players"
#define SET_GREEN_LOCATIONS "Place players"
#define FIRST_TEAM_WON_THE_SET "Green team won the set"
#define SECOND_TEAM_WON_THE_SET "Red team won the set"
#define FIRST_TEAM_WON_THE_MATCH  "Green won with "
#define SECOND_TEAM_WON_THE_MATCH "Red  won with "
#define MIN_LIMIT_Y 0
#define LENGTH_OF_SCORE_TABLE 300
#define X_OF_SCORE_TABLE WIDTH+(LENGTH_OF_SCORE_TABLE/4)
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include <math.h>
#include <set>
#include "RSDL/src/rsdl.hpp"
using namespace std;

#endif