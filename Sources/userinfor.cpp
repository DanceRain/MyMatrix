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
