#include "auth_window.h"
#include "ui_auth_window.h"

auth_window::auth_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::auth_window)
{
    ui->setupUi(this);
}

auth_window::~auth_window()
{
    delete ui;
}
