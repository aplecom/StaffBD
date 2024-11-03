#include "auth_window.h"
#include "ui_auth_window.h"

auth_window::auth_window(QWidget *parent)
    : QWidget(parent)
    , ui_Auth(new Ui::auth_window)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &auth_window::resetInfo);
    //QObject::connect(timer, SIGNAL(timeout()), this, SLOT(resetInfo())); //почему не работает ???

    ui_Auth->setupUi(this);
}

auth_window::~auth_window()
{
    delete ui_Auth;
}

void auth_window::on_loginBtn_clicked()
{
    emit login_button_clicked();
}


void auth_window::on_registerBtn_clicked()
{
    emit register_button_clicked();
}


void auth_window::on_loginLe_textEdited(const QString &arg1)
{
    auth_window::m_username= arg1;
}


void auth_window::on_passLe_textEdited(const QString &arg1)
{
    auth_window::m_userpass = arg1;
}


QString auth_window:: getLogin()
{
    return auth_window::m_username;
}

QString auth_window:: getPass()
{
    return auth_window::m_userpass;
}

void auth_window::printInfo(const QString& msg)
{
    ui_Auth->infoLb->setText(msg);
    timer->start(1500);
}

void auth_window::resetInfo()
{
    ui_Auth->infoLb->setText("");
}

