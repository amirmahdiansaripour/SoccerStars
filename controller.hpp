#ifndef CONTROLLER_H
#define CONTROLLER_H "CONTROLLER_H"
class Window;
class Controller{
public:
    Controller(Field&);
    void initial_screen(Window&);
    void initial_field();
    void handle_game();
    int handle_motion();
    void team_scored(int index);
    void handle_collisions();
private:
    Field match_field;
};
#endif