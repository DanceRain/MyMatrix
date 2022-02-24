#include "Headers/talk_to_server.h"
#include <boost/uuid/detail/md5.hpp>

Talk_To_Server::Talk_To_Server(const QUrl &url, QObject *parent):
    QObject (parent),
    m_url(url)
{
    qDebug() << "WebSocket server:" << url << endl;
    connect(&m_webSocket, &QWebSocket::connected, this, &Talk_To_Server::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Talk_To_Server::closed);
    connect(this, &Talk_To_Server::writeMessageList, this, &Talk_To_Server::sendMessageList);
    m_webSocket.open(m_url);
}

void Talk_To_Server::m_register(const QString& user_name, const QString& pwd)
{
    QJsonObject user_register_infor_obj;
    user_register_infor_obj.insert("user_name", user_name);
    user_register_infor_obj.insert("user_pwd", pwd);

    QJsonDocument user_register_infor_doc;
    user_register_infor_doc.setObject(user_register_infor_obj);
    QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);
    m_messageList.append(user_register_infor_str);
    emit writeMessageList();
}

void Talk_To_Server::m_login(const QString& user_id, const QString& pwd)
{

}

void Talk_To_Server::sendMessageList()
{
    qDebug() << "send some messages" << endl;
    while(!m_messageList.empty())
    {
        const QByteArray& data(m_messageList.front());
        m_messageList.pop_front();
        m_webSocket.sendBinaryMessage(data);
    }
}

void Talk_To_Server::onConnected()
{
    _is_connected = true;
    qDebug() << "connected" << endl;
}

void Talk_To_Server::onTextMessageReceived(QString message)
{

}
