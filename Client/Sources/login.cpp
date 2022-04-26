#include <QImage>
#include <QPixmap>
#include <QMouseEvent>

#include "ui_dialog.h"
#include "Headers/login.h"
#include "Headers/register.h"
#include "Headers/user_main_window.h"
#include "Headers/userinfor.h"
#include "Headers/httplib.h"
#include "Headers/talk_to_server.h"
#include <QPainter>
#include <qdebug.h>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent, Talk_To_Server* _Morpheus) :
    QWidget(parent),
    Morpheus(_Morpheus),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setStyle();
    setLog();
    this->setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_StyledBackground);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Dialog::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        IsMoving = true;
        mouseStartPoint = e->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void Dialog::Dialog::mouseMoveEvent(QMouseEvent* e)
{
    if(IsMoving)
    {
        QPoint distance = e->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        IsMoving = false;
    }
}

void Dialog::setLog()
{
    QImage img_Log(":/ui/image/icon/log.png");
    QPixmap pm_Log = QPixmap::fromImage(img_Log);
    ui->label_log->setPixmap(pm_Log.scaled(ui->label_log->size(),
                                       Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation));
}

void Dialog::setStyle()
{
    QString qss;
    QFile qssFile(":/qss/myStyle.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
    this->setWindowFlags(Qt::FramelessWindowHint);

}

void Dialog::on_pushButton_register_clicked()
{
    Register* qdlog_Register = new Register(this, nullptr, Morpheus);
    qdlog_Register->show();
    this->setVisible(false);
}

void Dialog::on_pushButton_login_clicked()
{
    if(!(ui->lineEdit_account->text().isEmpty()) && ui->lineEdit_password->text().size() >= 5)
    {
        QJsonObject ret = Morpheus->m_login(ui->lineEdit_account->text(), ui->lineEdit_password->text());
        if(ret["is_right"].toBool())
        {
            UserMainWindow* matrixMainWindow = new UserMainWindow(ui->lineEdit_account->text(), nullptr, Morpheus);
            matrixMainWindow->show();
            this->close();
        }
        else
        {
            QMessageBox::information(nullptr, "Login failed",
                                     "Please check your account or password");
        }
    }

}

void Dialog::paintEvent(QPaintEvent *event)
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
    //仍然要设置主窗体的背景透明
}
