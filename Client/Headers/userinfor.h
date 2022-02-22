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

public:
    QString getSNickName() const;
    void setSNickName(const QString& value);

    QPixmap getPixUserIcon() const;
    void setPixUserIcon(const QPixmap& value);

    QString getSUserArea() const;
    void setSUserArea(const QString& value);

    QString getSUserNote() const;
    void setSUserNote(const QString& value);

    QString getSUserNumber() const;
    void setSUserNumber(const QString& value);

    QPixmap getPixUserGender() const;
    void setPixUserGender(const QPixmap& value);

     QVector<QString> getVRecentMessage() const;


private:
    QString sNickName;
    QString sUserArea;
    QString sUserNote;
    QString sUserNumber;
    QPixmap pixUserGender;
    QPixmap pixUserIcon;
    QVector<QString> vRecentMessage;
};

#endif // USERINFOR_H
