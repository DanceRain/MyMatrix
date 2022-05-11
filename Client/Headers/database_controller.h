#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

#include "Headers/local_msg.h"
#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>

class DatabaseController
{
public:
    DatabaseController(const QString& user_name, const QString& pwd);
    void insertMessage(int receiver, const QString& message, int type);
    QVector<LocalMsg> selectMessage(int msg_ros);
    ~DatabaseController();
private:
    bool openDatabase();
    void closeDatabase();
    void createTable();
    QSqlDatabase database;
};

#endif // DATABASE_CONTROLLER_H
