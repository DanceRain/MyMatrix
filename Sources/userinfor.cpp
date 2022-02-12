#include "Headers/userinfor.h"

UserInfor::UserInfor(const QString& nickName, const QPixmap& userIcon, const QVector<QString>& recentMessage) :
    sNickName(nickName),
    pixUserIcon(userIcon),
    vRecentMessage(recentMessage)
{

}

QString UserInfor::getSNickName() const
{
    return sNickName;
}

QPixmap UserInfor::getPixUserIcon() const
{
    return pixUserIcon;
}

QVector<QString> UserInfor::getVRecentMessage() const
{
    return vRecentMessage;
}

QString UserInfor::getSUserNote() const
{
    return sUserNote;
}

void UserInfor::setSUserNote(const QString& value)
{
    sUserNote = value;
}

void UserInfor::setSNickName(const QString& value)
{
    sNickName = value;
}

QString UserInfor::getSUserArea() const
{
    return sUserArea;
}

void UserInfor::setSUserArea(const QString& value)
{
    sUserArea = value;
}

QString UserInfor::getSUserNumber() const
{
    return sUserNumber;
}

void UserInfor::setSUserNumber(const QString& value)
{
    sUserNumber = value;
}

QPixmap UserInfor::getPixUserGender() const
{
    return pixUserGender;
}

void UserInfor::setPixUserGender(const QPixmap& value)
{
    pixUserGender = value;
}

void UserInfor::setPixUserIcon(const QPixmap& value)
{
    pixUserIcon = value;
}
