#include <QImage>
#include <QPixmap>
#include <QMouseEvent>

#include "ui_dialog.h"
#include "Headers/dialog.h"
#include "Headers/register.h"
#include "Headers/usermainwindow.h"
#include "Headers/userinfor.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setStyle();
    setLog();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
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
}

void Dialog::on_pushButton_register_clicked()
{
    Register* qdlog_Register = new Register(nullptr, this);
    qdlog_Register->show();
    this->setVisible(false);
}

void Dialog::on_pushButton_login_clicked()
{
    QVector<UserInfor>* userData = new QVector<UserInfor>();
    QVector<QString>* message = new QVector<QString>();
    message->push_back("这是句测试");
    for(int i = 0; i < 100; ++i)
    {
        userData->push_back(UserInfor(QString("王桂鑫%1").arg(i), QPixmap(":/ui/image/icon/log.png"), *message));
    }
    UserMainWindow* userWindow = new UserMainWindow(nullptr, userData);
    userWindow->show();
//    this->hide();
    this->close();
}
