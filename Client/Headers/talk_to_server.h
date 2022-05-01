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
#include <QtWebSockets/QWebSocket>

class Talk_To_Server : public QObject
{
    Q_OBJECT
public:
    explicit Talk_To_Server(QObject *parent = nullptr);
    void startTalkInWs(const QString& user_id);

    QJsonObject m_login(const QString& user_id, const QString& user_pwd);
    QJsonObject m_register(const QString& user_name, const QString& user_pwd);
    QJsonObject m_requestUserInfor(const QString& user_id);
    void m_addFriend(const QString& friend_id, const QString& user_id);
    void m_requestMessage(const QString& user_id, QJsonObject& message);
    void m_responseAddFriend(bool IsAgreed, const QString& infor_receiver);
    void m_quit();
    void closeWs();

Q_SIGNALS:
    void writeMessageList();

Q_SIGNALS:
    void receivedMessage(QJsonObject& message);

private Q_SLOTS:
    void sendMessageList();
    void onConnected();
    void onTextMessageReceived(const QByteArray& message);

private:
    QJsonObject getJsonFromByteArray(const QByteArray& receivedData);

private:
    QString server_url;
    int http_server_port;
    int ws_server_port;
    httplib::Client client;
    QWebSocket m_webSocket;
    QList<QByteArray> m_messageList;
    QString user_id;
};

#endif // TALK_TO_SERVER_H
