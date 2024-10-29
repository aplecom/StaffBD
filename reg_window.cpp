#include "reg_window.h"
#include "ui_reg_window.h"

reg_window::reg_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::reg_window)
{
    ui->setupUi(this);
}

reg_window::~reg_window()
{
    delete ui;
}

void reg_window::on_registerBtn_clicked()
{
    emit register_button_clicked();
}


void reg_window::on_loginLe_textEdited(const QString &arg1)
{
    reg_window::m_userName = arg1;
}


void reg_window::on_passLe_textEdited(const QString &arg1)
{
    reg_window::m_userPass = arg1;
}

QString reg_window::getLogin()
{
    return m_userName;
}
QString reg_window::getPass()
{
    return m_userPass;
}


void reg_window::on_confirmLe_textEdited(const QString &arg1)
{
    reg_window::m_confirm = arg1;
}


bool reg_window::checkPass()
{
    return (m_confirm==getPass());
}

