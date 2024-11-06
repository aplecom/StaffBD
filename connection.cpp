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
    db_input = "INSERT INTO position (id,name,permissions) VALUES(4,'Стажер','Управляет только своими данными');";
    if(!query.exec(db_input))
        qDebug()<<"Ошибка добавления должности - Стажер"<<query.lastError().text();


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

    // добавляем информацию пользователя в personaldata
    str_t ="INSERT INTO personaldata (id) VALUES ('%1');";
    db_input = str_t.arg(userCounter);
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса"<<query.lastError().text()<<" : "<<query.lastQuery();
        return false;
    }

    // добавляем пользователя в employees
    query.prepare("INSERT INTO employees (id, login, password,personal_data_id, position_id,"
                  "access_id, department_id) VALUES (?, ?, ?, ?, ?, ?, ?);");
    query.addBindValue(userCounter); // id
    query.addBindValue(m_username); // login
    query.addBindValue(m_userpass); // password
    query.addBindValue(userCounter); // personal_data_id = id
    query.addBindValue(4); // position_id - стажер
    query.addBindValue(3); // access_id - начальный
    query.addBindValue(2); // department_id - back-end
    if(!query.exec())
    {
        qDebug() << "Не удалось добавить пользователя" << query.lastError().text() << " : " << query.lastQuery();
        return false;
    }

    // обновляем employee_id в personaldata для связи с employees
    str_t = "UPDATE personaldata SET employee_id = '%1' WHERE id = '%1'; ";
    db_input = str_t.arg(userCounter);
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса"<<query.lastError().text()<<" : "<<query.lastQuery();
        return false;
    }

    return true;
}


int Connection:: userAccess(QString& m_username)
{
    QString str_t;
    str_t = "SELECT access_id FROM employees WHERE login = '%1'";
    db_input = str_t.arg(m_username);
    query.exec(m_username);
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка получение уровня доступа"<<query.lastError().text();
        return -1;
    }
    else if(query.next())
    {
        int access_id = query.value(0).toInt();
        return access_id;
    }
    else
    {
        qDebug()<<"Пользователь "<<m_username<<"не найден";
        return -1;
    }
}

void Connection:: userData(QStringList& employees)
{
    QString str_t;
    int count = 0;
    str_t = "SELECT COUNT(*) FROM employees WHERE department_id = 2";
    db_input = str_t;

    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка получение количпества участников департамента"<<query.lastError().text();
    }
    else if(query.next())
    {
        count = query.value(0).toInt();
    }
    else
    {
         qDebug()<<"Пользователей департамента не найдено";
    }

    str_t = "SELECT login FROM employees WHERE department_id = 2";
    if (!query.exec(str_t)) {
        qDebug() << "Ошибка выполнения запроса на логины сотрудников:" << query.lastError().text();
    } else {
        while (query.next() && count > 0) {
            employees << query.value(0).toString();
            count--;
        }        }

}



