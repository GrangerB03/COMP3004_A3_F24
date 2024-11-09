#include "elevator.h"

//ECS* control_system;
//char direction; //1 for up, 0 for down
//int current_floor;
//Floor queued_floors[];
//int num_queued_floors;

Elevator::Elevator(){}

Elevator::Elevator(ECS* e){
    control_system = e;
    direction = 1;
    current_floor = 0;
    num_queued_floors = 0;
    for(int i = 0; i < NUM_PASSENGERS; i++){
        passengers[i] = NULL;
        queued_floors[i] = NULL;
    }
}

void Elevator::add_floor(Floor* f){
    //add floor to queue
    queued_floors[num_queued_floors] = f;
    num_queued_floors++;
    for(int i = 0; i < NUM_PASSENGERS; i++){
        if(f->get_passengers()[i] != NULL){
            //make sure we don't duplicate requests
            if(f->get_passengers()[i]->get_current_floor() != f->get_passengers()[i]->get_destination_floor()){
                    f->get_passengers()[i]->set_pressed_status(1);
            }
        }
    }
}

void Elevator::move(){
    //change current floor, direction accordingly depending on queue
    Floor* next_floor = queued_floors[0];
    if(num_queued_floors == 0){
        return;
    }
    if(direction == 1){
        //up
        if(next_floor->get_floor_number() > current_floor){
            //keep up direction
            //move up
            current_floor++;
        }else{
            //change direction
            //move down
            direction = 0;
            current_floor--;
        }
    }else{
        //down
        if(next_floor->get_floor_number() > current_floor){
            //change direction
            //move up
            direction = 1;
            current_floor++;
        }else{
            //keep down direction
            //move down
            current_floor--;
        }
    }

    passenger_handler(next_floor);
}

void Elevator::passenger_handler(Floor * next_floor){
    //after move, check if we have arrived at next floor
    for(int i = 0; i < NUM_PASSENGERS; i++){
        if(passengers[i] != NULL){
            passengers[i]->set_current_floor(current_floor);
        }
    }

    if(current_floor == next_floor->get_floor_number()){
        //delete next floor from queue
        queued_floors[0] = NULL;
        //rearrange queue
        for(int i = num_queued_floors; i >= 0; i--){
            queued_floors[i+1] = queued_floors[i];
        }
        //decrement queue size
        num_queued_floors--;
        //remove all passengers with this floor as destination floor
        for(int i = 0; i < NUM_PASSENGERS; i++){
            if(passengers[i] != NULL){
                if(passengers[i]->get_destination_floor() == next_floor->get_floor_number()){
                    passengers[i]->set_current_floor(next_floor->get_floor_number());
                    passengers[i]->set_in_elevator(0);
                    passengers[i]->set_pressed_status(0);
                    passengers[i] = NULL;
                }
            }
        }
        //add all passengers from this floor with destination floor in same direction as elevator
        Passenger** floor_passengers = next_floor->get_passengers();
        for(int i = 0; i < NUM_PASSENGERS; i++){
            if(floor_passengers[i] != NULL && floor_passengers[i]->get_pressed_status()){
                if(floor_passengers[i]->get_destination_floor() > floor_passengers[i]->get_current_floor()){
                    //passenger wants to go up
                        for(int j = 0; j < NUM_PASSENGERS; j++){
                            if(passengers[j] == NULL){
                                passengers[j] = floor_passengers[i];
                                passengers[j]->set_in_elevator(1);
                                if(floor_passengers[i] != NULL){
                                    for(int k = 0; k < NUM_FLOORS; k++){
                                        if(control_system->get_floors()[k]->get_floor_number() == floor_passengers[i]->get_destination_floor()){
                                            add_floor(control_system->get_floors()[k]);;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                }else{
                    //passenger wants to go down
                        for(int j = 0; j < NUM_PASSENGERS; j++){
                            if(passengers[j] == NULL){
                                passengers[j] = floor_passengers[i];
                                passengers[j]->set_in_elevator(1);
                                if(floor_passengers[i] != NULL){
                                    for(int k = 0; k < NUM_FLOORS; k++){
                                        if(control_system->get_floors()[k]->get_floor_number() == floor_passengers[i]->get_destination_floor()){
                                            add_floor(control_system->get_floors()[k]);;
                                        }
                                    }
                                }
                                break;
                            }
                        }

                }
            }
        }
    }
}

void Elevator::stop_movement(){
    //clear queue
    num_queued_floors = 0;
}

char Elevator::get_direction(){
    return direction;
}
\
int Elevator::get_current_floor(){
    return current_floor;
}

void Elevator::set_direction(char d){
    direction = d;
}

void Elevator::trigger_alarm(char a){
    switch(a){
        case 0:
            //help
            control_system->help_alarm();
        case 1:
            //fire
            control_system->fire_alarm();
        case 2:
            //overload
            control_system->overload_alarm();
        case 3:
            //power
            control_system->power_out_alarm();
        default:
            //error
            qInfo("Error occured from elevator alarm, invalid input to trigger_alarm in Elevator class");
    }
}
