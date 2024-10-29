#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QWidget>

namespace Ui {
class reg_window;
}

class reg_window : public QWidget
{
    Q_OBJECT

public:
    explicit reg_window(QWidget *parent = nullptr);
    ~reg_window();
    QString getName();
    QString getPass();
    bool checkPass();

signals:
    void register_button_clicked();

private slots:
    void on_registerBtn_clicked();
    void on_loginLe_textEdited(const QString &arg1);
    void on_passLe_textEdited(const QString &arg1);
    void on_confirmLe_textEdited(const QString &arg1);

private:
    Ui::reg_window *ui;
    QString m_userName;
    QString m_userPass;
    QString m_confirm;
};

#endif // REG_WINDOW_H
