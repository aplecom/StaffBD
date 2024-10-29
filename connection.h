#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QString>

class Connection{
private:
    QSqlDatabase db;
    QString db_input;
    bool m_loginSuccesfull;
    int userCounter;

public:
    Connection();
    void createConneсtion();
    void createTable();
    bool autoUser(QString& m_username,QString& m_userpass);

};


#endif // CONNECTION_H
