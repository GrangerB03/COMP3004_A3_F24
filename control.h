#ifndef CONTROL_H
#define CONTROL_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ecs.h"
#include "passenger.h"

#define NUM_FLOORS 5
#define NUM_PASSENGERS 4
#define NUM_ELEVATORS 2
#define MAX_STEPS 100

class ECS;

class Control
{
public:
    Control();
    void launch();
    void step(int);
    void set_steps(int*);
    ECS* get_control_system();
    Passenger** get_passengers();
    ~Control();
private:
    int steps[MAX_STEPS];
    ECS* control_system;
    Passenger* passengers[NUM_PASSENGERS];
};

#endif // CONTROL_H
