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
    connect(&ui_Reg,SIGNAL(back_button_clicked()),this,SLOT(backWindow()));

    connection.createConneсtion();
    connection.createTable();
    model = new QSqlTableModel;

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
    if ( m_username=="" || m_userpass=="")
        QMessageBox::information(0,"Ошибка","Данные не должны быть пустыми");
    else if(connection.autoUser(m_username,m_userpass))
    {
        ui_Auth.close();
        ui_Reg.close();
        printTable();
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
    m_username = ui_Reg.getLogin();
    m_userpass = ui_Reg.getPass();
    if ( m_username=="" || m_userpass=="")
        QMessageBox::information(0,"Ошибка","Данные не должны быть пустыми");
    else if(ui_Reg.checkPass())
    {
        if(connection.regUser(m_username,m_userpass))
        {
            ui_Reg.close();
            ui_Auth.show();
        }
        else
            QMessageBox::information(0,"Занято","Пользователь с таким логином уже существует");
    }
    else
        QMessageBox::information(0,"Ошибка","Пароли не совпадают");
}

void MainWindow::display()
{
    ui_Auth.show();
}

void MainWindow::backWindow()
{
    ui_Reg.close();
    ui_Auth.show();
}

void MainWindow::printTable(){

    model->setTable("employees");
    model->select();
    model->sort(0,Qt::AscendingOrder);

    ui_Main->tableView->setModel(model);
}
