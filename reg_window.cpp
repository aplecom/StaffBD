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
