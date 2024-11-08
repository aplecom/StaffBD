#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QSqlTableModel>
#include <QStringListModel>
#include<QStringList>

#include "auth_window.h"
#include "reg_window.h"
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();
    void printTable();

    void resetFields();
    void  setAccPage();

    void printList();


private:
    Ui::MainWindow *ui_Main;
    auth_window ui_auth;
    reg_window ui_reg;

    QString m_username;
    QString m_userpass;

    Connection connection;
    QSqlTableModel *modelTable;

    QStringListModel* modelList;
    QStringList employees;

    QPixmap pixmap;
    void setupDB();

private slots:
    void authorizeUser();
    void registerWindowShow();
    void registerUser();
    void backWindowAuth();
    void on_backBtn_clicked();


    void on_listView_pressed(const QModelIndex &index);

protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINWINDOW_H
