#include "Headers/database_controller.h"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


DatabaseController::DatabaseController(const QString& user_name, const QString& pwd):
    database(QSqlDatabase::addDatabase("QSQLITE"))
{
    qDebug() << "this is user_name" << user_name << endl;
    database.setDatabaseName(QString("%1.db").arg(user_name));
    database.setUserName(user_name);
    database.setPassword(pwd);
    openDatabase();
    createTable();
}

bool DatabaseController::openDatabase()
{
    if(database.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DatabaseController::closeDatabase()
{
    database.close();
}

void DatabaseController::createTable()
{
    QString query_str = QString("CREATE TABLE message_table (message_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                                "message_type interger(1) NOT NULL,"
                                "message_ros integer(8) NOT NULL, "
                                "message_content text(1024) NOT NULL)");
    QSqlQuery query;
    if(!query.exec(query_str))
    {
        qDebug() << query.lastError() << endl;
    }
    else
    {
        qDebug() << "Table Created" << endl;
    }
}

void DatabaseController::insertMessage(int ros, const QString& message, int type)
{

    QString query_str = QString("INSERT INTO message_table (message_type, message_ros, message_content) VALUES(?, ?, ?)");
    QSqlQuery query;
    query.prepare(query_str);
    query.addBindValue(type);
    query.addBindValue(ros);
    query.addBindValue(message);

    if(!query.exec())
    {
        qDebug() << query.lastError() << endl;
    }
    else
    {
        qDebug() << "Message Inserted" << endl;
    }
}


QVector<LocalMsg> DatabaseController::selectMessage(int message_ros)
{
    QVector<LocalMsg> ret;
    QString query_str = QString("SELECT message_id, message_type, message_content FROM message_table "
                                "WHERE message_ros = %1 ORDER BY message_id").arg(message_ros);
    QSqlQuery query;
    qDebug() << "query " << message_ros << " message" << endl;
    if(!query.exec(query_str))
    {
        qDebug() << query.lastError() << endl;
    }
    else
    {
        while(query.next())
        {
            ret.push_back(LocalMsg(query.value(0).toInt(), query.value(1).toInt(), message_ros, query.value(2).toString()));
        }
    }
    return ret;
}

DatabaseController::~DatabaseController()
{
    closeDatabase();
}


