#ifndef USERINFOR_H
#define USERINFOR_H

#include <QString>
#include <QPixmap>
#include <QVector>

class UserInfor
{
public:
    UserInfor(const QString& nickName, const QPixmap& userIcon, const QVector<QString>& vRecentMessage);
    ~UserInfor()
    {

    }
    QString getSNickName() const;
    QPixmap getPixUserIcon() const;
    QVector<QString> getVRecentMessage() const;

private:
    QString sNickName;
    QPixmap pixUserIcon;
    QVector<QString> vRecentMessage;
};

#endif // USERINFOR_H
