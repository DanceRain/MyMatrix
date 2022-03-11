#include "Headers/register.h"
#include "ui_register.h"

#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QMouseEvent>
#include <QMessageBox>
#include "Headers/talk_to_server.h"
#include <QRegExpValidator>
#include <QPainter>
#include "Headers/Matrix_Call.h"
#include "Headers/httplib.h"
#include <iostream>
#include <string>

Register::Register(Talk_To_Server* _deliver, QWidget *lastWindow, QWidget *parent) :
    m_deliver(_deliver),
    QDialog(parent),
    widget_lastWindow(lastWindow),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit_pwdIdentify->setEnabled(false);

    setStyle();
    setLog();
    setLineEditValidator();
}

Register::~Register()
{
    delete ui;
}

void Register::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        IsMoving = true;
        mouseStartPoint = e->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void Register::mouseMoveEvent(QMouseEvent* e)
{
    if(IsMoving)
    {
        QPoint distance = e->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void Register::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        IsMoving = false;
    }
}

void Register::setLog()
{
    QPixmap pm_Log(":/ui/image/icon/log.png");
    ui->label_log->setPixmap(pm_Log.scaled(ui->label_log->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
}

void Register::setStyle()
{
    QString qss;
    QFile qssFile(":/qss/register.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void Register::setLineEditValidator()
{
    QRegExp rx("[a-zA-Z0-9\u4e00-\u9fa5]+");
    QRegExpValidator* validator = new QRegExpValidator(rx, this);
    ui->lineEdit_account->setValidator(validator);
}

void Register::on_pushButton_shutdown_clicked()
{
    widget_lastWindow->setVisible(true);
    this->close();
}

void Register::on_pushButton_minimize_clicked()
{
    this->showMinimized();
}

void Register::on_pushButton_back_clicked()
{
    widget_lastWindow->setVisible(true);
    this->close();
}

void Register::on_lineEdit_pwdIdentify_textChanged(const QString &arg1)
{
    if(arg1 != ui->lineEdit_password->text())
    {
        ui->label_statusIdtiPwd->setPixmap(QPixmap(":/ui/image/icon/wrong.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    }
    else
    {
        ui->label_statusIdtiPwd->setPixmap(QPixmap(":/ui/image/icon/right.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    }
    if(arg1.compare(""))
    {
        ui->lineEdit_password->setEnabled(false);
    }
    else
    {
        ui->lineEdit_password->setEnabled(true);
    }
}

void Register::on_lineEdit_password_textChanged(const QString &arg1)
{
    if(arg1.size() < 8)
    {
        ui->label_statusPwd->setPixmap(QPixmap(":/ui/image/icon/wrong.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
        ui->lineEdit_pwdIdentify->setEnabled(false);
    }
    else
    {
        ui->label_statusPwd->setPixmap(QPixmap(":/ui/image/icon/right.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
        ui->lineEdit_pwdIdentify->setEnabled(true);
    }
}

void Register::on_pushButton_finReg_clicked()
{
    if(!(ui->lineEdit_account->text().compare(""))
            || (ui->lineEdit_pwdIdentify->text().compare(ui->lineEdit_password->text()))
            || (ui->lineEdit_password->text().size() < 8))
    {
        return;
    }
    else
    {
        QJsonObject user_register_infor_obj;
        user_register_infor_obj.insert("content_type", 1);
        user_register_infor_obj.insert("user_name", ui->lineEdit_account->text());
        user_register_infor_obj.insert("user_pwd", ui->lineEdit_password->text());
        QJsonDocument user_register_infor_doc;
        user_register_infor_doc.setObject(user_register_infor_obj);
        QByteArray user_register_infor_str = user_register_infor_doc.toJson(QJsonDocument::Compact);

        httplib::Client cli("112.126.96.244", 9999);
        auto res = cli.Post("/register", user_register_infor_str.toStdString(), "application/json");

        QJsonParseError jsonPraseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(res->body.c_str(), &jsonPraseError);

        inforUserNewId(jsonDoc.object()["new_id"].toString());
    }
}

void Register::on_lineEdit_account_textChanged(const QString &arg1)
{
    if(ui->lineEdit_account->text().compare(""))
    {
        ui->label_statusUser->setPixmap(QPixmap(":/ui/image/icon/right.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    }
    else
    {
        ui->label_statusUser->setPixmap(QPixmap(":/ui/image/icon/wrong.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    }
}

void Register::inforUserNewId(const QString& new_id)
{
    QString addZeroPrefixId(new_id);
    while(addZeroPrefixId.size() < 8)
    {
        addZeroPrefixId.push_front('0');
    }
    QMessageBox::information(nullptr, "Your Account",
                             "YOUR MATRIX CALL NUMBER IS " + addZeroPrefixId +
                             ", PLEASE KEEP FIRMLY IN MIND!");
}

void Register::paintEvent(QPaintEvent* event)
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
