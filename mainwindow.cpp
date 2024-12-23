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

    // может раскинуть по методам этот блок
    modelTable = new QSqlTableModel;
    modelList = new QStringListModel;

    // может раскинуть по методам этот блок

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

    modelTable->setTable("employees");
    //modelTable->select();
    modelTable->sort(0,Qt::AscendingOrder);
    ui_Main->tableView->setModel(modelTable);
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

    switch(page)
    {
        case 0:
            printTable();
            break;
        case 1:
            printList();
            break;
    }


}

void MainWindow:: printList()
{
    connection.userData(employees);
    modelList->setStringList(employees);
    ui_Main->listView->setModel(modelList);
}



void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    QStringList persData;

    // Логин ( можно потом вытащить из списка информации )
    QString login = index.data(Qt::DisplayRole).toString();
    ui_Main->loginLb->setText("Логин: " + login);


    connection.printPersData(login,persData);
    QString name = persData[0];
    QString surname =  persData[1];
    QString phone_number =  persData[2];
    QString email =  persData[3];
    QString address =  persData[4];
    QString additional_information =  persData[5];

    ui_Main->nameLb->setText("Имя: " + name);
    ui_Main->surnameLb->setText("Фамилия: "  + surname);
    ui_Main->numberLb->setText("Номер телефона: " + phone_number);
    ui_Main->emailLb->setText("Почта: " + email);
    ui_Main->addressLb->setText("Адрес: " + address);
    ui_Main->infoLb->setText("Дополнительная иформация: " + additional_information);


}
