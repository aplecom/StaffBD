#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
namespace Ui {
class auth_window;
}

class auth_window : public QWidget
{
    Q_OBJECT

public:
    explicit auth_window(QWidget *parent = nullptr);
    ~auth_window();
    QString getLogin();
    QString getPass();
    void printInfo(const QString& msg);
    void resetInfo();

signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();
    void on_loginLe_textEdited(const QString &arg1);
    void on_passLe_textEdited(const QString &arg1);


private:
    Ui::auth_window *ui_Auth;
    QString m_username;
    QString m_userpass;
    QTimer* timer;
    QPixmap pixmap;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // AUTH_WINDOW_H
