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

void Connection:: crTbEmployees()
{
    if(db.tables().contains("employees"))
    {
        qDebug()<<"Таблица employees уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input = "CREATE TABLE employees ("
               "id SERIAL PRIMARY KEY,"
               "login VARCHAR(50) UNIQUE NOT NULL,"
               "password VARCHAR(50) NOT NULL,"
               "position_id INTEGER REFERENCES position(id) ON DELETE SET NULL,"
               "department_id INTEGER REFERENCES department(id) ON DELETE SET NULL,"
               "access_id INTEGER REFERENCES accessLevel(id) ON DELETE SET NULL );";

    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError();
}

void Connection:: crTbDepartment()
{
    if(db.tables().contains("department"))
    {
        qDebug()<<"Таблица department уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input ="CREATE TABLE department ("
                "id SERIAL PRIMARY KEY,"
                "name VARCHAR(100) NOT NULL );";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError().text();

}

void Connection:: crTbPosition()
{
    if(db.tables().contains("position"))
    {
        qDebug()<<"Таблица position уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input ="CREATE TABLE position ("
                "id SERIAL PRIMARY KEY,"
                "name VARCHAR(100) NOT NULL,"
                "permissions TEXT);";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError().text();
}

void Connection:: crTbAccessLevel()
{
    if(db.tables().contains("accessLevel"))
    {
        qDebug()<<"Таблица accessLevel уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input = "CREATE TABLE accessLevel ("
                "id SERIAL PRIMARY KEY,"
                "level_name VARCHAR(50) NOT NULL,"
                "permissions TEXT);";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError().text();
}

void Connection:: crTbPersonalData()
{
    if(db.tables().contains("personalData"))
    {
        qDebug()<<"Таблица personalData уже существует";
        return;
    }
    QSqlQuery query(db);
    db_input = "CREATE TABLE personalData ("
               "id SERIAL PRIMARY KEY,"
               "name VARCHAR(50),"
               "surname VARCHAR(50),"
               "phone_number VARCHAR(11),"
               "email VARCHAR(100),"
               "address TEXT,"
               "additional_information TEXT);";

    if(!query.exec(db_input))
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError().text();
}

void Connection:: alTable()
{
    QSqlQuery query(db);
    db_input = "ALTER TABLE personalData ADD COLUMN employee_id INTEGER UNIQUE REFERENCES employees(id) ON DELETE CASCADE;";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления внешнего ключа: "<<query.lastError();

    db_input = "ALTER TABLE employees ADD COLUMN personal_data_id INTEGER UNIQUE REFERENCES personalData(id);";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления внешнего ключа: "<<query.lastError();

}

bool Connection::autoUser(const QString& m_username, const QString& m_userpass)
{
    QSqlQuery query(db);
    QSqlRecord rec;
    QString str_t = "SELECT * FROM employees WHERE login = '%1'";
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
    username = query.value(rec.indexOf("login")).toString();
    userpass = query.value(rec.indexOf("password")).toString();
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
    QString str_t = "SELECT * FROM employees WHERE login = '%1'";
    db_input = str_t.arg(m_username);
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса"<<query.lastError().text()<<" : "<<query.lastQuery();
    }
    query.next();
    rec = query.record();
    QString name = query.value(rec.indexOf("login")).toString();
    if(name==m_username)
        return false;

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
    }
    userCounter++;
    query.prepare("INSERT INTO employees (id, login, password) VALUES (?, ?, ?);");
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
