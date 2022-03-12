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


QJsonObject Talk_To_Server::login(const QString& user_id, const QString& user_pwd)
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
    }

    return jsonDoc.object();
}


