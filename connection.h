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
    bool autoUser(const QString& m_username, const QString& m_userpass);
    bool regUser(const QString& m_username,const QString& m_userpass);
    bool getLogS();
};


#endif // CONNECTION_H
