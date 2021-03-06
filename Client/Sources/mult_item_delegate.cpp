#include <QPainter>
#include <QDebug>
#include "Headers/mult_item_delegate.h"
#include "Headers/mult_item_data.h"

MuItemDelegate::MuItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void MuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole+1);
        MuItemData itemData = var.value<MuItemData>();

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());

        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#ebeced")));
            painter->setBrush(QColor("#ebeced"));
            painter->drawPath(path);
        }
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        }

        // 绘制图片，名字，最新消息位置区域
        QRect iconRect = QRect(rect.left(), rect.top() + 10, 60, 60);
        QRectF userNameRect = QRect(iconRect.right() + 10, iconRect.top(), rect.width()- 10 - iconRect.width(), 20);
        QRectF recentMessageRect = QRect(userNameRect.left(), userNameRect.bottom() + 10, rect.width()-10-iconRect.width(), 20);

        //避免画笔产生模糊
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->drawPixmap(iconRect, QPixmap(itemData.icon).scaled(60, 60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Microsoft Yahei", 10));
        painter->drawText(userNameRect, itemData.userName);

        painter->setPen(QPen(Qt::gray));
        painter->drawText(recentMessageRect, itemData.recentMessage);

        painter->restore();
    }
}

QSize MuItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 80);
}
