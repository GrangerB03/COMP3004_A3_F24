#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "control.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Control;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void set_control(Control*);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Control* control;
    void set_steps();
    int step;

private slots:
    void doSomething();
    void output();
    void set_passenger_values();
    void fire_alarm();
    void help_alarm();
    void door_alarm();
    void overload_alarm();
    void power_alarm();
};
#endif // MAINWINDOW_H
