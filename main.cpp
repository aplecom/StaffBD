#include "mainwindow.h"
#include "connection.h"
#include "reg_window.h"
#include "auth_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.display();
    return a.exec();
}
