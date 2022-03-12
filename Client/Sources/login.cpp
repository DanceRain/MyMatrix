#include <QImage>
#include <QPixmap>
#include <QMouseEvent>

#include "ui_dialog.h"
#include "Headers/login.h"
#include "Headers/register.h"
#include "Headers/user_main_window.h"
#include "Headers/userinfor.h"
#include "Headers/httplib.h"
#include <QPainter>
#include <qdebug.h>

Dialog::Dialog(QWidget *parent) :
    QWidget(parent),
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
    Register* qdlog_Register = new Register(this);
    qdlog_Register->show();
    this->setVisible(false);
}

void Dialog::on_pushButton_login_clicked()
{
    if(!(ui->lineEdit_account->text().isEmpty()) && ui->lineEdit_password->text().size() >= 5)
    {
       QJsonObject user_register_infor_obj;
       user_register_infor_obj.insert("content_type", 2);
       user_register_infor_obj.insert("user_id", ui->lineEdit_account->text());
       user_register_infor_obj.insert("user_pwd", ui->lineEdit_password->text());
       QJsonDocument user_register_infor_doc;
       user_register_infor_doc.setObject(user_register_infor_obj);
       QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);

       qDebug() << user_register_infor_str << endl;

       unsigned port = 9999;
       httplib::Client cli("112.126.96.244", port);
       auto res = cli.Post("/login", user_register_infor_str.toStdString(), "application/json");

       QJsonParseError jsonPraseError;
       QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);
       if(jsonDoc["is_right"].toBool())
       {
           QVector<UserInfor>* userData = new QVector<UserInfor>();
           QVector<QString>* message = new QVector<QString>();
           message->push_back("这是句测试");
           for(int i = 0; i < 100; ++i)
           {
               userData->push_back(UserInfor(QString("王桂鑫%1").arg(i), QPixmap(":/ui/image/icon/log.png"), *message));
           }
           (*userData)[0].setSUserArea("中国 湖北");
           (*userData)[0].setSUserNumber("000001");
           (*userData)[0].setSUserNote("这是我自己");
           (*userData)[0].setPixUserGender(QPixmap(":/ui/image/icon/famale.jpg"));
           (*userData)[0].setSUserNote("这是我自己");
           UserMainWindow* userWindow = new UserMainWindow(nullptr, userData);
           userWindow->show();
        //   this->hide();
           this->close();
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
