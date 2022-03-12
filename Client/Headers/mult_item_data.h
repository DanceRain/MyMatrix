#ifndef MULT_ITEM_DATA_H
#define MULT_ITEM_DATA_H

#include <QMetaType>
#include <QString>
#include <QPixmap>

typedef struct {
    QPixmap icon;
    QString userName;
    QString recentMessage;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)

#endif // MULT_ITEM_DATA_H
