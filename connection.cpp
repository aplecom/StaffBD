#include "connection.h"

bool createConnetion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Staff");
    db.setUserName("ilya");
    db.setPassword("");
    if(!db.open())
    {
        QMessageBox::warning(0,"Ошибка",db.lastError().text());
        return false;
    }
    else{
        QMessageBox::warning(0,"Успешно","Соединение с БД установлено!");
        return true;
    }
}
bool createTable()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        QMessageBox::warning(0, "Ошибка", "Соединение с БД не установлено!");
        return false;
    }

    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS employees (
            id SERIAL PRIMARY KEY,
            name VARCHAR(100) NOT NULL,
            age INT NOT NULL
        )
    )";

    if (!query.exec(createTableQuery))
    {
        QMessageBox::warning(0, "Ошибка", query.lastError().text());
        return false;
    }

    QMessageBox::information(0, "Успешно", "Таблица 'employees' успешно создана!");
    return true;
}
