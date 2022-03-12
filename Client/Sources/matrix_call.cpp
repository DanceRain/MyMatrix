#include "Headers/Matrix_Call.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

Matrix_Call::Matrix_Call(QObject *parent) :
    QObject(parent),
    manger(new QNetworkAccessManager(this))
{
    connect(manger, &QNetworkAccessManager::finished, this, &Matrix_Call::replyFinished);
}

void Matrix_Call::postData(const QByteArray& data)
{
    QNetworkRequest request;

    QUrl url("112.126.96.244:9999");
    request.setUrl(url);
    manger->post(request, data);
    qDebug() << "post something" << endl;
}

Matrix_Call::~Matrix_Call()
{

}

void Matrix_Call::replyFinished(QNetworkReply* rep)
{
    QByteArray bts = rep->readAll();
    QString str = QString::fromUtf8(bts);
    qDebug() << "Reply:" << str;
    rep->deleteLater();
}
