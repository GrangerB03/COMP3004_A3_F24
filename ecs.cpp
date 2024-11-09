#include "ecs.h"

//Elevator elevators[];
//Floor* floors[];

ECS::ECS()
{
    emergency_stoppage = 0;
}

void ECS::set_elevators(Elevator* e[]){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i] = e[i];
    }
}

void ECS::set_floors(Floor* f[]){
    for(int i = 0; i < NUM_FLOORS; i++){
        floors[i] = f[i];
    }
}

Elevator** ECS::get_elevators(){
    return elevators;
}

Floor** ECS::get_floors(){
    return floors;
}

void ECS::request_elevator(char d,  Floor* f){
    //request elevator in d direction, f floor

    for(int i = 0; i < NUM_ELEVATORS; i++){
        if(elevators[i]->get_direction() == d){
            elevators[i]->add_floor(f);
            return;
        }
    }
    //failsafe incase no direction is found
    elevators[0]->add_floor(f);
}

void ECS::move_elevators(){
    //do things
    for(int i = 0; i < NUM_ELEVATORS;  i++){
        elevators[i]->move();
    }
}

void ECS::help_alarm(){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i]->stop_movement();
    }
    emergency_stoppage = 1;
}

void ECS::fire_alarm(){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i]->stop_movement();
    }
    emergency_stoppage = 1;
}

void ECS::overload_alarm(){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i]->stop_movement();
    }
    emergency_stoppage = 1;
}

void ECS::power_out_alarm(){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i]->stop_movement();
    }
    emergency_stoppage = 1;
}

void ECS::door_alarm(){
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i]->stop_movement();
    }
    emergency_stoppage = 1;
}

bool ECS::get_emergency_stoppage(){
    return emergency_stoppage;
}
