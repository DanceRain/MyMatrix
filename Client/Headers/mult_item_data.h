#ifndef MULT_ITEM_DATA_H
#define MULT_ITEM_DATA_H

#include <QMetaType>
#include <QString>
#include <QPixmap>

typedef struct {
    int userAccount;
    QString userName;
    QPixmap icon;
    short userGender;
    QString userArea;
    QString recentMessage;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)

#endif // MULT_ITEM_DATA_H
