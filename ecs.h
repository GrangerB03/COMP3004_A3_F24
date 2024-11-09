#ifndef ECS_H
#define ECS_H

#include "elevator.h"
#include "control.h"
#include "floor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define NUM_FLOORS 5
#define NUM_PASSENGERS 4
#define NUM_ELEVATORS 2

class Elevator;
class Floor;

class ECS
{
public:
    ECS();
    void set_elevators(Elevator*[]);
    void set_floors(Floor*[]);
    Elevator** get_elevators();
    Floor** get_floors();
    void request_elevator(char, Floor*); //to be called by floor class, char is direction, int floor number
    void move_elevators();
    void help_alarm();
    void fire_alarm();
    void overload_alarm();
    void power_out_alarm();
    void door_alarm();
    bool get_emergency_stoppage();
private:
    Elevator* elevators[NUM_ELEVATORS];
    Floor* floors[NUM_FLOORS];
    bool emergency_stoppage;
};

#endif // ECS_H
