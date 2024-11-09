#include "control.h"

/**
 * @brief Control::Control
 * The constructor creates all necessary objects for the simulation to function.
 */
Control::Control()
{
    //setup ECS
    control_system = new ECS();

    //setup elevators
    Elevator* tmp[NUM_ELEVATORS];
    for(int i = 0; i < NUM_ELEVATORS; i++){
        tmp[i] = new Elevator(control_system);
    }
    control_system->set_elevators(tmp);

    //setup floors
    Floor* tmp2[NUM_FLOORS];
    for(int i = 0; i < NUM_FLOORS; i++){
        tmp2[i] = new Floor(i);
        tmp2[i]->set_control_system(control_system);
    }
    control_system->set_floors(tmp2);

    //setup passengers control->launch();
    for(int i = 0; i < NUM_PASSENGERS; i++){
        passengers[i] = new Passenger(i);
    }
}

ECS* Control::get_control_system(){
    return control_system;
}

Passenger** Control::get_passengers(){
    return passengers;
}

void Control::set_steps(int * s){
    for(int i = 0; i < MAX_STEPS; i++){
        steps[i] = s[i];
    }
}

void Control::step(int step_num){

    if(control_system->get_emergency_stoppage()){
        return;
    }

    if(steps[step_num] != -1){
        Passenger* p = passengers[steps[step_num]];

        for(int i = 0; i < NUM_FLOORS; i++){
            if(control_system->get_floors()[i]->get_floor_number() == p->get_current_floor()){
                control_system->get_floors()[i]->add_passenger(p);
                control_system->request_elevator(p->get_current_floor() < p->get_destination_floor() ? 1 : 0, control_system->get_floors()[i]);
            }
        }
    }
    control_system->move_elevators();
}

void Control::launch(){
    qInfo("Simulation start");
}

Control::~Control(){
    delete(&control_system);
}
