#include "floor.h"

//int floor_number;
//Elevator elevators_present[];
//ECS* control_system;
//Passenger passengers[];

//empty constructor to keep c++ happy
Floor::Floor()
{}

Floor::Floor(int f){
    floor_number = f;
    for(int i= 0; i < NUM_PASSENGERS; i++){
        passengers[i] = NULL;
    }
}
void Floor::set_control_system(ECS* e){
    control_system = e;
}

int Floor::get_floor_number(){
    return floor_number;
}

void Floor::add_passenger(Passenger *p){
    passengers[p->get_id()] = p;
}

Passenger** Floor::get_passengers(){
    return passengers;
}

void Floor::request_elevator(char d){
    //ask ECS nicely for direction
    control_system->request_elevator(d, this);
}
Floor::~Floor(){
    //delete urself
}
