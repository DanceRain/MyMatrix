#include "Headers/talk_to_server.h"

#include <QDebug>
using namespace std;

Talk_To_Server::Talk_To_Server(QObject *parent):
    QObject (parent),
    server_url("112.126.96.244"),
    http_server_port(9999),
    ws_server_port(10000),
    client(httplib::Client(server_url.toStdString(), http_server_port))
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Talk_To_Server::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Talk_To_Server::closed);
    connect(this, &Talk_To_Server::writeMessageList, this, &Talk_To_Server::sendMessageList);
}


/*content-type:
 * 1 注册
 * 2 登录
 * 3 获取用户个人信息，包括好友列表初始化信息
 * 4 请求添加好友信息
 * 5 请求添加好友信息回复
 * 6 用户消息
 */
QJsonObject Talk_To_Server::m_login(const QString& user_id, const QString& user_pwd)
{
    QJsonObject ret;
    if(server_url.isEmpty() || http_server_port == 0)
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
    if(server_url.isEmpty() || http_server_port == 0)
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
    if(server_url.isEmpty() || http_server_port == 0)
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

void Talk_To_Server::m_addFriend(const QString& friend_id, const QString& user_id)
{
    QJsonObject user_add_friend_obj;
    user_add_friend_obj.insert("content_type", 4);
    user_add_friend_obj.insert("user_id", user_id);
    user_add_friend_obj.insert("friend_id", friend_id);


    QJsonDocument user_add_friend_doc(user_add_friend_obj);
    QByteArray user_register_infor_str = user_add_friend_doc.toJson(QJsonDocument::Compact);
    m_messageList.push_back(user_register_infor_str);
    emit writeMessageList();
}

void Talk_To_Server::m_requestMessage(const QString& user_id, QJsonObject& message)
{
    if(server_url.isEmpty() || http_server_port == 0)
    {
        message.insert("error", "can't find server");
        return;
    }

    QJsonObject user_add_friend_obj;
    user_add_friend_obj.insert("content_type", 6);
    user_add_friend_obj.insert("user_id", user_id);

    QJsonDocument user_add_friend_doc;
    user_add_friend_doc.setObject(user_add_friend_obj);
    QByteArray user_add_friend_str = user_add_friend_doc.toJson(QJsonDocument::Compact);


    auto res = client.Post("/getMessage", user_add_friend_str.toStdString(), "application/json");

    QJsonParseError jsonPraseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);
    qDebug() << "this is response JsonDoc" << jsonDoc << endl;
    if(jsonPraseError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonPraseError.error;
        message.insert("error", "json prase error");
        return;
    }

    message = jsonDoc.object();
}

void Talk_To_Server::startTalkInWs(const QString& user_id)
{
    qDebug() << "start open" << endl;
    this->user_id = user_id;
    m_webSocket.open(QUrl("ws://112.126.96.244:10000"));
}

void Talk_To_Server::sendMessageList()
{
    while(!m_messageList.empty())
    {
        const QByteArray& data(m_messageList.front());
        qDebug() << data << endl;
        m_messageList.pop_front();
        m_webSocket.sendBinaryMessage(data);
    }
}

void Talk_To_Server::onConnected()
{
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
                this, &Talk_To_Server::onTextMessageReceived);

    //发送一条验证信息，让服务器产生ws_id与user_id之间的映射
    QJsonObject user_verify_friend_obj;
    user_verify_friend_obj.insert("content_type", 9);
    user_verify_friend_obj.insert("user_id", user_id);
    QJsonDocument user_verify_friend_doc(user_verify_friend_obj);
    QByteArray user_verify_friend_str = user_verify_friend_doc.toJson(QJsonDocument::Compact);
    m_messageList.push_back(user_verify_friend_str);
    emit writeMessageList();
}

void Talk_To_Server::onTextMessageReceived(const QByteArray& message)
{
    QJsonObject decode_data = getJsonFromByteArray(message);
    emit receivedMessage(decode_data);
}

QJsonObject Talk_To_Server::getJsonFromByteArray(const QByteArray& receivedData)
{
    QJsonParseError jsonPraseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(receivedData, &jsonPraseError);
    return jsonDoc.object();
}


