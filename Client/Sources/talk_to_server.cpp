#include "Headers/talk_to_server.h"

#include <QDebug>
using namespace std;

Talk_To_Server::Talk_To_Server(QObject *parent):
    QObject (parent),
    server_url("112.126.96.244"),
    server_port(9999),
    client(httplib::Client(server_url, server_port))
{

}

QJsonObject Talk_To_Server::m_login(const QString& user_id, const QString& user_pwd)
{
    QJsonObject ret;
    if(server_url.empty() || server_port == 0)
    {
        ret.insert("error", "can't find server");
        return ret;
    }

    QJsonObject user_register_infor_obj;
    user_register_infor_obj.insert("content_type", 2);
    user_register_infor_obj.insert("user_id", user_id);
    user_register_infor_obj.insert("user_pwd", user_pwd);

    QJsonDocument user_register_infor_doc;
    user_register_infor_doc.setObject(user_register_infor_obj);
    QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);

    auto res = client.Post("/login", user_register_infor_str.toStdString(), "application/json");

    QJsonParseError jsonPraseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);

    if(jsonPraseError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonPraseError.error;
        return ret;
    }

    return jsonDoc.object();
}

QJsonObject Talk_To_Server::m_register(const QString& user_name, const QString& user_pwd)
{
    QJsonObject ret;
    if(server_url.empty() || server_port == 0)
    {
        ret.insert("error", "can't find server");
        return ret;
    }

    QJsonObject user_register_infor_obj;
    user_register_infor_obj.insert("content_type", 1);
    user_register_infor_obj.insert("user_name", user_name);
    user_register_infor_obj.insert("user_pwd", user_pwd);

    QJsonDocument user_register_infor_doc;
    user_register_infor_doc.setObject(user_register_infor_obj);
    QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);

    auto res = client.Post("/register", user_register_infor_str.toStdString(), "application/json");

    QJsonParseError jsonPraseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);

    if(jsonPraseError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonPraseError.error;
        return ret;
    }

    return jsonDoc.object();
}

QJsonObject Talk_To_Server::m_requestUserInfor(const QString& user_id)
{
    QJsonObject ret;
    if(server_url.empty() || server_port == 0)
    {
        ret.insert("error", "can't find server");
        return ret;
    }

    QJsonObject user_register_infor_obj;
    user_register_infor_obj.insert("content_type", 3);
    user_register_infor_obj.insert("user_id", user_id);

    QJsonDocument user_register_infor_doc;
    user_register_infor_doc.setObject(user_register_infor_obj);
    QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);
    qDebug() << user_register_infor_doc;
    auto res = client.Post("/request", user_register_infor_str.toStdString(), "application/json");

    QJsonParseError jsonPraseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);
    qDebug() << "this is response JsonDoc" << jsonDoc.toBinaryData() << endl;
    if(jsonPraseError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonPraseError.error;
        return ret;
    }

    return jsonDoc.object();
}


