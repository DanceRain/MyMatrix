#ifndef MATRIX_CALL_H
#define MATRIX_CALL_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class Matrix_Call : public QObject
{
    Q_OBJECT
public:
    explicit Matrix_Call(QObject *parent = nullptr);
    void postData(const QByteArray& data);
    ~Matrix_Call();

public slots:
    void replyFinished(QNetworkReply* rep);
private:
    QNetworkAccessManager* manger;
    QNetworkReply* reply;
};

#endif // MATRIX_CALL_H
