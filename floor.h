#ifndef FLOOR_H
#define FLOOR_H

#include "elevator.h"
#include "passenger.h"
#include "ecs.h"

#define NUM_FLOORS 5
#define NUM_PASSENGERS 4
#define NUM_ELEVATORS 2

class ECS;
class Elevator;

class Floor
{
public:
    Floor();
    Floor(int);
    int get_floor_number();
    Passenger** get_passengers();
    void add_passenger(Passenger*);
    void set_control_system(ECS*);
    void request_elevator(char);
    ~Floor();
private:
    int floor_number;
    ECS* control_system;
    Passenger* passengers[NUM_PASSENGERS];
};

#endif // FLOOR_H
