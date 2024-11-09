#include "mainwindow.h"
#include <QApplication>
#include "control.h"
#include "ecs.h"
#include "elevator.h"
#include "floor.h"
#include "passenger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control c;
    MainWindow w;
    w.set_control(&c);
    w.show();
    return a.exec();
}
