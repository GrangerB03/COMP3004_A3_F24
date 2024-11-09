#include "passenger.h"
#include <QApplication>

Passenger::Passenger(){
    current_floor = 0;
    in_elevator = 0;
    destination_floor = 0;
    button_pressed = 0;
    qInfo("Creating Passenger!");
}

Passenger::Passenger(int id)
{
    current_floor = 0;
    in_elevator = 0;
    destination_floor = 0;
    button_pressed = 0;
    this->id = id;
    qInfo("Creating Passenger in const 2!");
}


//getters and setters for fields, passenger class is pretty much a puppet
void Passenger::set_current_floor(int c){
    current_floor = c;
}

void Passenger::set_in_elevator(bool i){
    in_elevator = i;
}

int Passenger::get_id(){
    return id;
}

void Passenger::set_id(int i){
    id = i;
}

void Passenger::set_destination_floor(int d){
    destination_floor = d;
}

int Passenger::get_current_floor(){
    return current_floor;
}

bool Passenger::get_in_elevator(){
    return in_elevator;
}

int Passenger::get_destination_floor(){
    return destination_floor;
}

bool Passenger::get_pressed_status(){
    return button_pressed;
}

void Passenger::set_pressed_status(bool b){
    button_pressed = b;
}
