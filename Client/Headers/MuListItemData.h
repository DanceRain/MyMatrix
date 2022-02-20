#ifndef MULISTITEMDATA_H
#define MULISTITEMDATA_H

#include <QMetaType>
#include <QString>
#include <QPixmap>

typedef struct {
    QPixmap icon;
    QString userName;
    QString recentMessage;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)

#endif // MULISTITEMDATA_H
