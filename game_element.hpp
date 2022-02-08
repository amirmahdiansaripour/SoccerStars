#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H "GAME_ELEMENT_H"

class Team;

class Game_element{
public:
    Game_element();

    Game_element(Point, Team*, int);

    Team* get_team_of_player();

    float get_mass_of_player();

    Point get_position_of_player();

    void change_velocity(Point);

    Point get_velocity();

    int get_shirt_num();

    void reset_locations();

    bool sign_changed(float, float);

    void change_position_of_player();

    bool get_first_position();

    void assign_instant_position(Point);

    bool dont_reflect(Point);

    Point calculate_phisycal_position(float, float);

    Point reflect_if_need(Point, int, int);

    Point put_in_suitable_place(Point);

    void assign_first_position(Point);

    void calculate_velocity(Point);
private:
	float mass;
	Point position;
	Point velocity;
    Team* team;
    bool first_position_choosed;
    Point first_position;
    int player_shirt_num;
};

#endif