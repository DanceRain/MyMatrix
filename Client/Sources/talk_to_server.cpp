#include "Headers/talk_to_server.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <boost/uuid/detail/md5.hpp>

Talk_To_Server::Talk_To_Server(const QUrl &url, QObject *parent):
    QObject (parent),
    m_url(url)
{
    qDebug() << "WebSocket server:" << url << endl;
    connect(&m_webSocket, &QWebSocket::connected, this, &Talk_To_Server::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Talk_To_Server::closed);
    m_webSocket.open(m_url);
}

void Talk_To_Server::m_register(const QString& user_name, const QString& pwd)
{
    if(!_is_connected)
    {
        return;
    }
    QJsonObject user_register_infor_obj;
    user_register_infor_obj.insert("user_name", user_name);
    user_register_infor_obj.insert("user_pwd", pwd);

    QJsonDocument user_register_infor_doc;
    user_register_infor_doc.setObject(user_register_infor_obj);
    QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);
    qDebug() << user_register_infor_str << endl;
    m_webSocket.sendBinaryMessage(user_register_infor_str);
}

void Talk_To_Server::m_login(const QString& user_id, const QString& pwd)
{

}

void Talk_To_Server::onConnected()
{
    qDebug() << "connected success" << endl;
    m_webSocket.sendBinaryMessage(QByteArray("fuck off"));
}

void Talk_To_Server::onTextMessageReceived(QString message)
{

}
