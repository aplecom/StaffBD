#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::MainWindow)
{
    connect(&ui_auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_auth, SIGNAL(register_button_clicked()), this, SLOT(registerWindowShow()));
    connect(&ui_reg, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_reg, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_reg, SIGNAL(back_button_clicked()), this, SLOT(backWindowAuth()));

    pixmap.load(":/resource/img/background.jpg");

    setupDB();

    modelTable = new QSqlTableModel;
    modelList = new QStringListModel;

    ui_Main->setupUi(this);

    setupMenu();
}

MainWindow::~MainWindow()
{
    delete ui_Main;
}

void MainWindow::setupDB()
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

void MainWindow::setupMenu()
{
    QMenuBar *menuBar = this->menuBar();

    // Мейн меню
    QMenu *mainMenu = new QMenu("Файл", this);
    QAction *logoutAction = new QAction("Выйти", this);

    mainMenu->addAction(logoutAction);

    menuBar->addMenu(mainMenu);

    // Меню запроса доступа
    QMenu *editMenu = new QMenu("Редактировать", this);
    QAction *editProfileAction = new QAction("Редактировать профиль", this);
    QAction *manageUsersAction = new QAction("Управление пользователями", this);

    editMenu->addAction(editProfileAction);
    editMenu->addAction(manageUsersAction);

    menuBar->addMenu(editMenu);


    connect(editProfileAction, &QAction::triggered, this, &MainWindow::editProfile);
    connect(manageUsersAction, &QAction::triggered, this, &MainWindow::manageUsers);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::on_backBtn_clicked);
}

void MainWindow::authorizeUser()
{
    m_username = ui_auth.getLogin();
    m_userpass = ui_auth.getPass();

    if (m_username.isEmpty() || m_userpass.isEmpty()) {
        ui_auth.printInfo("Заполните поля");
        return;
    }

    if (connection.autoUser(m_username, m_userpass)) {
        ui_auth.close();
        ui_reg.close();
        setAccPage();
        this->show();
    } else {
        ui_auth.printInfo("Пользователя с таким логином или паролем не существует");
    }
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

    if (m_username.isEmpty() || m_userpass.isEmpty()) {
        ui_reg.printInfo("Заполните поля");
        return;
    }

    if (ui_reg.checkPass()) {
        if (connection.regUser(m_username, m_userpass)) {
            resetFields();
            ui_reg.close();
            ui_auth.show();
        } else if (m_username.length() > 20 || m_userpass.length() > 12) {
            ui_reg.printInfo("Сократите логин или пароль");
        } else {
            ui_reg.printInfo("Пользователь с таким логином уже существует");
        }
    } else {
        ui_reg.printInfo("Пароли не совпадают");
    }
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

void MainWindow::printTable(QString tb)
{
    modelTable->setTable(tb);
    modelTable->sort(0, Qt::AscendingOrder);
    ui_Main->tableView->setModel(modelTable);


    ui_Main->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
// TO DO: Перенести все на такой интерфейс
void MainWindow::printList()
{
    connection.userData(employees);
    modelList->setStringList(employees);
    ui_Main->listView->setModel(modelList);
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

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QSize windowSize = size();

    painter.drawPixmap(0, 0, windowSize.width(), windowSize.height(), pixmap);
}

void MainWindow::setAccPage()
{
    int page = connection.userAccess(m_username) - 1;
    ui_Main->stackedWidget->setCurrentIndex(page);
    pixmap.load(":/resource/img/background2.jpg");

    switch (page) {
    case 0:
        showAdminPage();
        break;
    case 1:
        showModerPage();
        break;
    default:
        showDefaultPage();
        break;
    }
}

void MainWindow::showAdminPage()
{
    printTable("personalData");
    //ui_Main->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ui_Main->adminLabel->setText("Добро пожаловать, администратор");
    // Дополнительные действия для администратора
}

void MainWindow::showModerPage()
{
    printTable("personalData");
    //ui_Main->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ui_Main->adminLabel->setText("Добро пожаловать, администратор");
    // Дополнительные действия для модератора таблицы
}


// void MainWindow::showUserPage()
// {
//     printTable();
//     //printList();
//     //ui_Main->userLabel->setText("Добро пожаловать, пользователь");
//     // Дополнительные действия для пользователя
// }

void MainWindow::showDefaultPage()
{
    printTable("personalData");
    ui_Main->stackedWidget->setCurrentIndex(0);
    //ui_Main->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ui_Main->tableView->setColumnHidden(0, true);  // Пример скрытия столбца
    //ui_Main->defaultLabel->setText("Добро пожаловать");
    // Действия по умолчанию
}

void MainWindow::editProfile()
{
    if (connection.userAccess(m_username) > 2) {
        QMessageBox::information(this, "Редактирование таблиц", "У вас нет прав на управление пользователями.");
        return;
    }
    printTable("personalData");
    ui_Main->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    // Логика редактирования профиля
    //QMessageBox::information(this, "Редактировать таблицы", "Функция редактирования таблиц в разработке.");
}

void MainWindow::manageUsers()
{
    if (connection.userAccess(m_username) > 1) {
        QMessageBox::information(this, "Управление пользователями", "У вас нет прав на управление пользователями.");
        return;
    }
    printTable("employees");
    ui_Main->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    // Логика управления пользователями
    //QMessageBox::information(this, "Управление пользователями", "Функция управления пользователями в разработке.");
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    QStringList persData;

    QString login = index.data(Qt::DisplayRole).toString();
    ui_Main->loginLb->setText("Логин: " + login);

    connection.printPersData(login, persData);

    if (persData.size() >= 6) {
        ui_Main->nameLb->setText("Имя: " + persData[0]);
        ui_Main->surnameLb->setText("Фамилия: " + persData[1]);
        ui_Main->numberLb->setText("Номер телефона: " + persData[2]);
        ui_Main->emailLb->setText("Почта: " + persData[3]);
        ui_Main->addressLb->setText("Адрес: " + persData[4]);
        ui_Main->infoLb->setText("Дополнительная информация: " + persData[5]);
    } else {
        ui_Main->infoLb->setText("Недостаточно данных о пользователе");
    }
}
