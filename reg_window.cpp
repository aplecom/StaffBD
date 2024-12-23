#include "reg_window.h"
#include "ui_reg_window.h"

reg_window::reg_window(QWidget *parent)
    : QWidget(parent)
    , ui_Reg(new Ui::reg_window)
{

    pixmap.load(":/resource/img/background.jpg");

    timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &reg_window::resetInfo);

    ui_Reg->setupUi(this);
}

reg_window::~reg_window()
{
    delete ui_Reg;
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

void reg_window::on_backBtn_clicked()
{
    emit back_button_clicked();
}

void reg_window::printInfo(const QString& msg)
{
    ui_Reg->infoLb->setText(msg);
    timer->start(1000);
}

void reg_window::resetInfo()
{
    ui_Reg->infoLb->setText("");
}

void reg_window::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QSize windowSize = size();

    painter.drawPixmap(0, 0, windowSize.width(), windowSize.height(), pixmap);
}

void reg_window::resetFields()
{
    ui_Reg->loginLe->textEdited("");
    ui_Reg->passLe->textEdited("");
    ui_Reg->confirmLe->textEdited("");
    ui_Reg->loginLe->setText("");
    ui_Reg->passLe->setText("");
    ui_Reg->confirmLe->setText("");
}
