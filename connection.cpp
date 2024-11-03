#include "connection.h"


Connection::Connection(): query(QSqlQuery())
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
    else
        query = QSqlQuery(db);
}

void Connection:: crTbEmployees()
{

    if(db.tables().contains("employees"))
    {
        qDebug()<<"Таблица employees уже существует";
        return;
    }

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

    db_input = "ALTER TABLE personalData ADD COLUMN employee_id INTEGER UNIQUE REFERENCES employees(id) ON DELETE CASCADE;";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления внешнего ключа: "<<query.lastError().text();

    db_input = "ALTER TABLE employees ADD COLUMN personal_data_id INTEGER UNIQUE REFERENCES personalData(id);";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления внешнего ключа: "<<query.lastError().text();
}

void Connection:: fstInsTable()
{
    // accessLevel
    db_input = "INSERT INTO accessLevel (id,level_name,permissions) VALUES(1,'Полный доступ','Может исправлять абсолютно все для"
               " каждого сотрудника любого департамента');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления уровня доступа - Полный доступ"<<query.lastError().text();
    db_input = "INSERT INTO accessLevel (id,level_name,permissions) VALUES(2,'Доступ департамента','Может исправлять информацию для"
               " каждого сотрудника его департамента');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления уровня доступа - Доступ департамента"<<query.lastError().text();
    db_input = "INSERT INTO accessLevel (id,level_name,permissions) VALUES(3,'Начальный доступ','Может исправлять только свою информацию');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления уровня доступа - Начальный доступ"<<query.lastError().text();

    // position
    db_input = "INSERT INTO position (id,name,permissions) VALUES(1,'Администратор','Управляет всеми отделами');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления должности - Администратор"<<query.lastError().text();
    db_input = "INSERT INTO position (id,name,permissions) VALUES(2,'Главный инженер','Управляет своим отделом');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления должности - Главный инженер"<<query.lastError().text();
    db_input = "INSERT INTO position (id,name,permissions) VALUES(3,'Инженер','Управляет только своими данными');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления должности - Инженер"<<query.lastError().text();

    // department
    db_input = "INSERT INTO department (id,name) VALUES(1,'Control');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления департамента - Control"<<query.lastError().text();
    db_input = "INSERT INTO department (id,name) VALUES(2,'Back-end');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления департамента - Back-end"<<query.lastError().text();
    db_input = "INSERT INTO department (id,name) VALUES(3,'Front-end');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления департамента - Front-end"<<query.lastError().text();
    db_input = "INSERT INTO department (id,name) VALUES(4,'QA');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления департамента - QA"<<query.lastError().text();
}

bool Connection::autoUser(const QString& m_username, const QString& m_userpass)
{

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
    if(m_username != username || m_userpass != userpass)
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
        userCounter = query.value(0).toInt() + 1;
    }
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
