#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include "control.h"
#include "ecs.h"
#include "elevator.h"
#include "floor.h"
#include "passenger.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    step = 0;
    connect(ui->stepButton, SIGNAL(released()), this, SLOT(doSomething()));
    connect(ui->stepButton, SIGNAL(released()), this, SLOT(output()));
    connect(ui->Door_Alarm_Button, SIGNAL(released()), this, SLOT(door_alarm()));
    connect(ui->Fire_Alarm_Button, SIGNAL(released()), this, SLOT(fire_alarm()));
    connect(ui->Power_Out_Button, SIGNAL(released()), this, SLOT(power_alarm()));
    connect(ui->Overload_Alarm_Button, SIGNAL(released()), this, SLOT(overload_alarm()));
    connect(ui->Help_Alarm_Button, SIGNAL(released()), this, SLOT(help_alarm()));
    connect(ui->set_passenger_values_button, SIGNAL(released()), this, SLOT(set_passenger_values()));
}

void MainWindow::set_control(Control* c){
    control = c;

    control->launch();
}

void MainWindow::doSomething(){
    qInfo("Hello world");
}

void MainWindow::set_passenger_values(){
    //initalize passenger values from user input
    int start_floor;
    int dest_floor;
    QString output = "";

    start_floor = ui->passenger0_starting_floor->currentText().toInt();
    dest_floor = ui->passenger0_dest_floor->currentText().toInt();
    control->get_passengers()[0]->set_current_floor(start_floor);
    control->get_passengers()[0]->set_destination_floor(dest_floor);
    control->get_passengers()[0]->set_in_elevator(0);
    //control->get_control_system()->get_floors()[start_floor]->add_passenger(control->get_passengers()[0]);
    output.append("Passenger 0: \nCurrent Floor: ");
    output.append(QString::number(start_floor));
    output.append("\nDestination Floor: ");
    output.append(QString::number(dest_floor));
    output.append("\nIn Elevator: FALSE");
    output.append("\nButton Pressed Status: FALSE");
    ui->passenger0Output->setPlainText(output);
    output = "";

    start_floor = ui->passenger1_starting_floor->currentText().toInt();
    dest_floor = ui->passenger1_dest_floor->currentText().toInt();
    control->get_passengers()[1]->set_current_floor(start_floor);
    control->get_passengers()[1]->set_destination_floor(dest_floor);
    control->get_passengers()[1]->set_in_elevator(0);
    //control->get_control_system()->get_floors()[start_floor]->add_passenger(control->get_passengers()[1]);
    output.append("Passenger 1: \nCurrent Floor: ");
    output.append(QString::number(start_floor));
    output.append("\nDestination Floor: ");
    output.append(QString::number(dest_floor));
    output.append("\nIn Elevator: FALSE");
    output.append("\nButton Pressed Status: FALSE");
    ui->passenger1Output->setPlainText(output);
    output = "";

    start_floor = ui->passenger2_starting_floor->currentText().toInt();
    dest_floor = ui->passenger2_dest_floor->currentText().toInt();
    control->get_passengers()[2]->set_current_floor(start_floor);
    control->get_passengers()[2]->set_destination_floor(dest_floor);
    control->get_passengers()[2]->set_in_elevator(0);
    //control->get_control_system()->get_floors()[start_floor]->add_passenger(control->get_passengers()[2]);
    output.append("Passenger 2: \nCurrent Floor: ");
    output.append(QString::number(start_floor));
    output.append("\nDestination Floor: ");
    output.append(QString::number(dest_floor));
    output.append("\nIn Elevator: FALSE");
    output.append("\nButton Pressed Status: FALSE");
    ui->passenger2Output->setPlainText(output);
    output = "";

    start_floor = ui->passenger3_starting_floor->currentText().toInt();
    dest_floor = ui->passenger3_dest_floor->currentText().toInt();
    control->get_passengers()[3]->set_current_floor(start_floor);
    control->get_passengers()[3]->set_destination_floor(dest_floor);
    control->get_passengers()[3]->set_in_elevator(0);
    //control->get_control_system()->get_floors()[start_floor]->add_passenger(control->get_passengers()[3]);
    output.append("Passenger 3: \nCurrent Floor: ");
    output.append(QString::number(start_floor));
    output.append("\nDestination Floor: ");
    output.append(QString::number(dest_floor));
    output.append("\nIn Elevator: FALSE");
    output.append("\nButton Pressed Status: FALSE");
    ui->passenger3Output->setPlainText(output);
    output = "";

    set_steps();
}

void MainWindow::set_steps(){
    //take step input, store passenger index in step
    int p0_step = ui->passenger0_button_press_step->value();
    int p1_step = ui->passenger1_button_press_step->value();
    int p2_step = ui->passenger2_button_press_step->value();
    int p3_step = ui->passenger3_button_press_step->value();

    int steps[MAX_STEPS];

    for(int i = 0; i < MAX_STEPS; i++){
        if(i == p0_step){
            steps[i] = 0;
        }else if(i == p1_step){
            steps[i] = 1;
        }else if(i == p2_step){
            steps[i] = 2;
        }else if(i == p3_step){
            steps[i] = 3;
        }else{
            steps[i] = -1;
        }
    }

    control->set_steps(steps);
}

//update function
void MainWindow::output(){
    control->step(++step);
    ECS* ecs = control->get_control_system();
    if(ecs->get_emergency_stoppage()){
        ui->textOutput->setPlainText("EMERGENCY STOPPAGE IN EFFECT, RESET SIMULATION");
        return;
    }
    QString str = "Simulation Step: ";
    QString str2 = QString::number(step);
    str.append(str2);
    ui->simulationTimeOutput->setPlainText(str);

    for(int i = 0; i < NUM_ELEVATORS; i++){
        QString output = "";
        int current_floor = ecs->get_elevators()[i]->get_current_floor();
        char direction = ecs->get_elevators()[i]->get_direction();
        if(direction){
            output.append("Direction: UP\n");
        }else{
            output.append("Direction: DOWN\n");
        }

        output.append("CURRENTLY ON FLOOR: ");
        output.append(QString::number(current_floor));
        output.append("\n");
        if(i == 0){
            ui->elevator0Output->setPlainText(output);
        }else{
            ui->elevator1Output->setPlainText(output);
        }
    }

    QString output = "";
    Passenger* p = control->get_passengers()[0];
    output.append("Passenger 0: \nCurrent Floor: ");
    output.append(QString::number(p->get_current_floor()));
    output.append("\nDestination Floor: ");
    output.append(QString::number(p->get_destination_floor()));
    output.append("\nIn Elevator: ");
    output.append(p->get_in_elevator() ? "TRUE" : "FALSE");
    output.append("\nButton Pressed Status: ");
    output.append(p->get_pressed_status() ? "TRUE" : "FALSE");
    ui->passenger0Output->setPlainText(output);
    output = "";

    p = control->get_passengers()[1];
    output.append("Passenger 1: \nCurrent Floor: ");
    output.append(QString::number(p->get_current_floor()));
    output.append("\nDestination Floor: ");
    output.append(QString::number(p->get_destination_floor()));
    output.append("\nIn Elevator: ");
    output.append(p->get_in_elevator() ? "TRUE" : "FALSE");
    output.append("\nButton Pressed Status: ");
    output.append(p->get_pressed_status() ? "TRUE" : "FALSE");
    ui->passenger1Output->setPlainText(output);
    output = "";

    p = control->get_passengers()[2];
    output.append("Passenger 2: \nCurrent Floor: ");
    output.append(QString::number(p->get_current_floor()));
    output.append("\nDestination Floor: ");
    output.append(QString::number(p->get_destination_floor()));
    output.append("\nIn Elevator: ");
    output.append(p->get_in_elevator() ? "TRUE" : "FALSE");
    output.append("\nButton Pressed Status: ");
    output.append(p->get_pressed_status() ? "TRUE" : "FALSE");
    ui->passenger2Output->setPlainText(output);
    output = "";

    p = control->get_passengers()[3];
    output.append("Passenger 3: \nCurrent Floor: ");
    output.append(QString::number(p->get_current_floor()));
    output.append("\nDestination Floor: ");
    output.append(QString::number(p->get_destination_floor()));
    output.append("\nIn Elevator: ");
    output.append(p->get_in_elevator() ? "TRUE" : "FALSE");
    output.append("\nButton Pressed Status: ");
    output.append(p->get_pressed_status() ? "TRUE" : "FALSE");
    ui->passenger3Output->setPlainText(output);
    output = "";
}

void MainWindow::fire_alarm(){
    control->get_control_system()->fire_alarm();
}

void MainWindow::help_alarm(){
    control->get_control_system()->help_alarm();
}

void MainWindow::door_alarm(){
    control->get_control_system()->door_alarm();
}

void MainWindow::overload_alarm(){
    control->get_control_system()->overload_alarm();
}

void MainWindow::power_alarm(){
    control->get_control_system()->power_out_alarm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

