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
    {
        QMessageBox::warning(0,"Ошибка",db.lastError().text());
    }
    else{
        QMessageBox::warning(0,"Успешно","Соединение с БД установлено!");
    }
}

void Connection:: createTable()
{
    QSqlQuery query(db);
    db_input = "CREATE TABLE employees ( "
                   "number INTEGER PRIMARY KEY NOT NULL,"
                   "name VARCHAR(20), "
                   "pass VARCHAR(12));";

    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка создания таблицы: "<<query.lastError();
        QMessageBox::warning(0,"Ошибка","Создание таблицы не произошло");
    }
    else
        QMessageBox::warning(0,"Успешно","Создана таблица");

}

bool Connection::autoUser(QString& m_username,QString& m_userpass)
{
    QSqlQuery query(db);
    QSqlRecord rec;
    QString str_t = "SELECT * FROM employees WHERE name = '%1'";


    QString username = "";
    QString userpass = "";

    db_input = str_t.arg(m_username);

    if(!query.exec(db_input))
    {
        qDebug()<<"Не удается выполнить запрос"<<query.lastError()<<" : "<<query.lastQuery();
        QMessageBox::warning(0,"Ошибка","Не удалось выполнить запрос на поиск поля");
        return false;
    }
    QMessageBox::warning(0,"Успех","Удалось выполнить запрос на поиск поля");
    rec = query.record(); // метаданные ( какие есть поля в табл)
    query.next(); // переход к первой записи
    userCounter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();
    if(m_username != username || m_userpass != userpass)
    {
        qDebug() << "Данные неверны" << username << " " << userpass;
        QMessageBox::warning(0,"Ошибка","Данные неверны");
         return false;
    }
    m_loginSuccesfull = true;
    return true;
}


