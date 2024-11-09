#ifndef PASSENGER_H
#define PASSENGER_H


class Passenger
{
public:
    Passenger();
    Passenger(int);
    void set_current_floor(int);
    void set_in_elevator(bool);
    void set_destination_floor(int);
    int get_current_floor();
    bool get_in_elevator();
    int get_destination_floor();
    int get_id();
    void set_id(int);
    bool get_pressed_status();
    void set_pressed_status(bool);
private:
    int id;
    int current_floor;
    bool in_elevator;
    int destination_floor;
    bool button_pressed;
};

#endif // PASSENGER_H
