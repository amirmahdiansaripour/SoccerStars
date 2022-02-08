#ifndef FIELD_H
#define FIELD_H "FIELD_H"
class Team;
class Game_element;

struct Collision{
	Game_element* first_player;
	Game_element* second_player;
};
typedef struct Collision Collision;

class Field{
public:
    Field(Window*);
    
    Field();

    Window* get_table();

    void change_turn(int);

    vector<Collision>* get_collisions();

    void add_team(Team);
    void reset_velocities();
    void add_ball(Game_element);

    vector<Team>* get_teams();

    Game_element* get_ball();

    void reset_locations();

    void print_message(string, const RGB);

    void initial();

    void print_turn_or_match_finished(int ,string ,string);

    void change_velocities_when_collision(vector<Collision>*);

    Event get_last_event();

    Game_element* choose_player_to_move();

    void show_state();

    void show_num_of_goals(Point, Point, Point, int);
    
    void handle_delay(int, int, int);

    Point choose_first_positions(Point ,int);

    void all_have_initial_pos();

    bool get_initial_positions();

    Point left_click_is_released();

    void change_positions_after_collision();

    bool elements_are_inert();

    int check_if_any_team_won_a_set();

    int check_if_any_team_scored();

    int check_if_any_team_won_the_match();

    void handle_goal(int);

    void show_turn(string, int ,Point ,Point ,const RGB);

    void enter_team_score(int, int, int, const RGB, string);
private:
	vector<Team>* teams;
	Game_element ball;
    Window* game_table;
    int num_of_goals_to_win_the_match;
    int num_of_matches;
    int team_turn;
    bool initial_positions_choosed;
};
#endif