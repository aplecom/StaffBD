#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::MainWindow)
{
    connect(&ui_auth,SIGNAL(login_button_clicked()),this,SLOT(authorizeUser()));
    connect(&ui_auth,SIGNAL(destroyed()),this,SLOT(show()));
    connect(&ui_auth,SIGNAL(register_button_clicked()),this,SLOT(registerWindowShow()));
    connect(&ui_reg,SIGNAL(register_button_clicked()),this,SLOT(registerUser()));
    connect(&ui_reg,SIGNAL(destroyed()),this,SLOT(show()));
    connect(&ui_reg,SIGNAL(back_button_clicked()),this,SLOT(backWindowAuth()));

    pixmap.load(":/resource/img/background.jpg");

    setupDB();
    model = new QSqlTableModel;
    model->setTable("employees");
    ui_Main->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_Main;
}

void MainWindow:: setupDB()
{
    connection.createConneсtion();
    connection.crTbAccessLevel();
    connection.crTbDepartment();
    connection.crTbPosition();
    connection.crTbPersonalData();
    connection.crTbEmployees();
    connection.alTable();
    connection.fstInsTable();
}

void MainWindow::authorizeUser()
{
    m_username = ui_auth.getLogin();
    m_userpass = ui_auth.getPass();
    if ( m_username=="" || m_userpass=="")
    {
         ui_auth.printInfo("Заполните поля");
    }

    else if(connection.autoUser(m_username,m_userpass))
    {
        ui_auth.close();
        ui_reg.close();
        setAccPage();
        printTable();
        this->show();
    }
    else
        ui_auth.printInfo("Пользователя с таким логином или паролем не существует");

}
void MainWindow::registerWindowShow()
{
    ui_auth.hide();
    ui_reg.show();
}
void MainWindow::registerUser()
{
    m_username = ui_reg.getLogin();
    m_userpass = ui_reg.getPass();
    if ( m_username=="" || m_userpass=="")
        ui_reg.printInfo("Заполните поля");

    else if(ui_reg.checkPass())
    {
        if(connection.regUser(m_username,m_userpass))
        {
            resetFields();
            ui_reg.close();
            ui_auth.show();
        }
        else if(m_username.length()>20 || m_userpass.length() > 12)
            ui_reg.printInfo("Сократите логин или пароль");
        else
            ui_reg.printInfo("Пользователь с таким логином уже существует");
    }
    else
        ui_reg.printInfo("Пароли не совпадают");

}

void MainWindow::display()
{
    ui_auth.show();
}

void MainWindow::backWindowAuth()
{
    resetFields();
    ui_reg.close();
    ui_auth.show();
}

void MainWindow::printTable(){

    model->select();
    model->sort(0,Qt::AscendingOrder);
    ui_Main->tableView->setModel(model);
}

void MainWindow::on_backBtn_clicked()
{
    this->close();
    ui_auth.show();
}

void MainWindow::resetFields()
{
    ui_auth.resetFields();
    ui_reg.resetFields();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QSize windowSize = size();

    painter.drawPixmap(0, 0, windowSize.width(), windowSize.height(), pixmap);
}

void MainWindow:: setAccPage()
{
    int page = connection.userAccess(m_username) - 1;
    ui_Main->stackedWidget->setCurrentIndex(page);
    pixmap.load(":/resource/img/background2.jpg");
}
