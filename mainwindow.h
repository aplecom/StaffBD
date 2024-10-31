#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QString>
#include <QSqlTableModel>

#include "auth_window.h"
#include "reg_window.h"
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlTableModel *model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();
    void printTable();


private:
    Ui::MainWindow *ui_Main;

    auth_window ui_Auth;
    reg_window ui_Reg;

    QString m_username;
    QString m_userpass;

    Connection connection;

private slots:
    void authorizeUser();
    void registerWindowShow();
    void registerUser();
    void backWindow();
};
#endif // MAINWINDOW_H
