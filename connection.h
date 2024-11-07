#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>

class Connection{
private:
    QSqlDatabase db;
    QString db_input;
    QSqlQuery query;
    bool m_loginSuccesfull;
    int userCounter;

public:
    Connection();
    void createConneсtion();
    void crTbEmployees();
    void crTbDepartment();
    void crTbPosition();
    void crTbAccessLevel();
    void crTbPersonalData();
    void alTable();
    void fstInsTable();
    bool autoUser(const QString& m_username, const QString& m_userpass);
    bool regUser(const QString& m_username,const QString& m_userpass);
    bool getLogS();
    int userAccess(QString& m_username);
    void userData(QStringList& employees);
    void printPersData(QString& login,QStringList& persData);


};


#endif // CONNECTION_H
