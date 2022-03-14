#ifndef TALK_TO_SERVER_H
#define TALK_TO_SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <string>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QByteArray>
#include "Headers/httplib.h"

class Talk_To_Server : public QObject
{
    Q_OBJECT
public:
    explicit Talk_To_Server(QObject *parent = nullptr);
    QJsonObject m_login(const QString& user_id, const QString& user_pwd);
    QJsonObject m_register(const QString& user_name, const QString& user_pwd);
    QJsonObject m_requestUserInfor(const QString& user_id);
private:
    std::string server_url;
    int server_port;
    httplib::Client client;
};

#endif // TALK_TO_SERVER_H
