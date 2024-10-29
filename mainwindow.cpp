#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::MainWindow)
{
    connect(&ui_Auth,SIGNAL(login_button_clicked()),this,SLOT(authorizeUser()));
    connect(&ui_Auth,SIGNAL(destroyed()),this,SLOT(show()));
    connect(&ui_Auth,SIGNAL(register_button_clicked()),this,SLOT(registerWindowShow()));
    connect(&ui_Reg,SIGNAL(register_button_clicked()),this,SLOT(registerUser()));
    connect(&ui_Reg,SIGNAL(destroyed()),this,SLOT(show()));

    connection.createConneсtion();
    connection.createTable();


    ui_Main->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_Main;
}

void MainWindow::authorizeUser()
{
    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();

    if(connection.autoUser(m_username,m_userpass))
    {
        ui_Auth.close();
        ui_Reg.close();
        this->show();
    }
}
void MainWindow::registerWindowShow()
{
    ui_Auth.hide();
    ui_Reg.show();
}
void MainWindow::registerUser()
{

}

void MainWindow::display()
{
    ui_Auth.show();
}
