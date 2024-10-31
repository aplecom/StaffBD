#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class reg_window;
}

class reg_window : public QWidget
{
    Q_OBJECT

public:
    explicit reg_window(QWidget *parent = nullptr);
    ~reg_window();
    QString getLogin();
    QString getPass();
    bool checkPass();
    void printInfo(const QString& msg);
    void resetInfo();

signals:
    void register_button_clicked();
    void back_button_clicked();

private slots:
    void on_registerBtn_clicked();
    void on_loginLe_textEdited(const QString &arg1);
    void on_passLe_textEdited(const QString &arg1);
    void on_confirmLe_textEdited(const QString &arg1);
    void on_backBtn_clicked();

private:
    Ui::reg_window *ui_Reg;
    QString m_userName;
    QString m_userPass;
    QString m_confirm;
    QTimer* timer;
};

#endif // REG_WINDOW_H
