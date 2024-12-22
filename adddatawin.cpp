#include "adddatawin.h"

AddDataWin::AddDataWin(QWidget *parent) :
    QDialog(parent),
    ui_add(new Ui::AddDataWin)
{
    ui_add->setupUi(this);
}

void AddDataWin::on_addBtn_clicked()
{
    QString name = ui_add->nameLineEdit->text();
    QString surname = ui_add->surnameLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString email = ui->emailLineEdit->text();

    // Генерация сигнала с данными
    emit dataAdded(name, surname, phone, email);

    this->accept();  // Закрыть окно
}


AddDataWin::~AddDataWin()
{
    delete ui;
}
