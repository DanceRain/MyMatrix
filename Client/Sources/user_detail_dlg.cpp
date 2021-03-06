#include "Headers/user_detail_dlg.h"
#include "ui_userdetaildlg.h"
#include <QFile>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPainter>

UserDetailDlg::UserDetailDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDetailDlg)
{
    ui->setupUi(this);
    setStyle();
    setAttribute(Qt::WA_StyledBackground);
}

UserDetailDlg::~UserDetailDlg()
{
    delete ui;
}

void UserDetailDlg::setUserIcon(const QPixmap& pix_UserIcon)
{
    ui->label_userIcon->setPixmap(pix_UserIcon.scaled(ui->label_userIcon->size(),
                                                      Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QPixmap UserDetailDlg::getUserIcon() const
{
    return *(ui->label_userIcon->pixmap());
}

void UserDetailDlg::setUserName(const QString& s_UserName)
{
    ui->label_userName->setText(s_UserName);
}

QString UserDetailDlg::getUserName() const
{
    return ui->label_userName->text();
}

void UserDetailDlg::setUserGender(const QPixmap& pix_UserGender)
{
    ui->label_userGender->setPixmap(pix_UserGender.scaled(ui->label_userGender->size(),
                                                          Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void UserDetailDlg::setUserNote(const QString& s_UserNote)
{
    ui->label_noteVal->setText(s_UserNote);
}

void UserDetailDlg::setUserCallNumber(const QString& s_UserCallNumber)
{
    ui->label_numberVal->setText(s_UserCallNumber);
}

void UserDetailDlg::setUserArea(const QString& s_UserArea)
{
    ui->label_areaVal->setText(s_UserArea);
}

void UserDetailDlg::setStyle()
{
    QString qss;
    QFile qssFile(":/qss/userDetailDlg.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
}

void UserDetailDlg::paintEvent(QPaintEvent* event)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, this->width(), this->height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<1; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(1-i, 1-i, this->width()-(1-i)*2, this->height()-(1-i)*2);
        color.setAlpha(150);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
