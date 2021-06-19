#include "mainwindow.h"
#include <QApplication>
#include "BUS_QEV_Act.h"
#include <pthread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
#if 0
    pthread_t thread1;
    int error = pthread_create(&thread1, NULL,key_control_fun, NULL);
    if(0 != error)
    {
        printf("pthread_create failed");
    }
#endif

    vehicle::qev::vehicle_acticvity Veh_Act;
    Veh_Act.VehicleParsingFunc(1);

    return a.exec();
}
