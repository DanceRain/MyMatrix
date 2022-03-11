#ifndef TALK_TO_SERVER_H
#define TALK_TO_SERVER_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QByteArray>

class Talk_To_Server : public QObject
{
    Q_OBJECT
public:
    explicit Talk_To_Server(const QUrl &url, QObject *parent = nullptr);
public:
    void m_register(const QString& user_name, const QString& pwd);
    void m_login(const QString& user_id, const QString& pwd);
Q_SIGNALS:
    void closed();
    void writeMessageList();
    void receivedNewId(const QString& new_id);

private Q_SLOTS:
    void sendMessageList();
    void onConnected();
    void onTextMessageReceived(const QByteArray& message);

private:
    QJsonObject getJsonFromByteArray(const QByteArray& receivedData);

private:
    bool _is_connected = false;
    QUrl m_url;

private:
    QWebSocket m_webSocket;
    QList<QByteArray> m_messageList;
};

#endif // TALK_TO_SERVER_H
