#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "floor.h"
#include "ecs.h"

#define NUM_FLOORS 5
#define NUM_PASSENGERS 4
#define NUM_ELEVATORS 2

class ECS;

class Elevator
{
public:
    Elevator();
    Elevator(ECS*);
    void add_floor(Floor*);
    int get_current_floor();
    void move();
    void stop_movement();
    char get_direction();
    void set_direction(char);
    void trigger_alarm(char); //0 is help alarm, 1 is fire alarm, 2 is overload alarm, 3 is power alarm
private:
    ECS* control_system;
    char direction; //1 for up, 0 for down
    int current_floor;
    int num_queued_floors;
    void passenger_handler(Floor*);
    Passenger* passengers[NUM_PASSENGERS];
    Floor* queued_floors[NUM_PASSENGERS];
};

#endif // ELEVATOR_H
