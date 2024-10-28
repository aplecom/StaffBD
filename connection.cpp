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
