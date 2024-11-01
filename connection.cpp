#include "connection.h"


Connection::Connection()
{
    m_loginSuccesfull = false;
    userCounter = 0;
}
void Connection::createConneсtion()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Staff");
    db.setUserName("ilya");
    db.setPassword("");
    if(!db.open())
        qDebug()<<"Не удалось открыть БД "<<db.lastError().text();
}

void Connection:: createTable()
{
    if(db.tables().contains("employees"))
    {
        qDebug()<<"Таблица employees уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input = "CREATE TABLE employees ( "
                   "number INTEGER PRIMARY KEY NOT NULL,"
                   "name VARCHAR(20), "
                   "pass VARCHAR(12));";

    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError().text();
}

bool Connection::autoUser(const QString& m_username, const QString& m_userpass)
{
    QSqlQuery query(db);
    QSqlRecord rec;
    QString str_t = "SELECT * FROM employees WHERE name = '%1'";
    QString username;
    QString userpass;

    db_input = str_t.arg(m_username);

    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса "<<query.lastError().text()<<" : "<<query.lastQuery();
        return false;
    }

    query.next();
    rec = query.record(); // метаданные ( имена столбцов, индексы и типы данных)

    userCounter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();
    if(m_username != username || m_userpass != userpass || m_username == "")
    {

        qDebug() << "Данные неверны" << username << " " << userpass;
        return false;
    }
    m_loginSuccesfull = true;
    return true;
}

bool Connection::getLogS()
{
    return m_loginSuccesfull;
}

bool Connection::regUser(const QString& m_username,const QString& m_userpass)
{
    QSqlQuery query(db);
    QSqlRecord rec;
    QString str_t = "SELECT * FROM employees WHERE name = '%1'";
    db_input = str_t.arg(m_username);
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса"<<query.lastError().text()<<" : "<<query.lastQuery();
    }
    query.next();
    rec = query.record();
    QString name = query.value(rec.indexOf("name")).toString();
    if(name==m_username)
        return false;
    // сюда все перенести

    str_t = "SELECT COUNT(*) FROM employees;";
    db_input = str_t;
    if(!query.exec(db_input))
    {
        qDebug() << "Не удается получить номер при регистрации " << query.lastError().text() << " : " << query.lastQuery();
        return false;
    }
    else {
        query.next();
        rec = query.record();
        userCounter = query.value(0).toInt();
        qDebug() << userCounter;
    }
    userCounter++;
    query.prepare("INSERT INTO employees (number, name, pass) VALUES (?, ?, ?);");
    query.addBindValue(userCounter);
    query.addBindValue(m_username);
    query.addBindValue(m_userpass);
    if(!query.exec())
    {
        qDebug() << "Не удалось добавить данные в БД"  << query.lastError().text() << " : " << query.lastQuery();
        return false;
    }
    return true;
}
