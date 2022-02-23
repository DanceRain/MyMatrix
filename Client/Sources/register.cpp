#include "Headers/register.h"
#include "ui_register.h"

#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QMouseEvent>
#include <QRegExpValidator>
#include "Headers/talk_to_server.h"

Register::Register(QWidget *parent, QWidget *lastWindow) :
    QDialog(parent),
    widget_lastWindow(lastWindow),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
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
    }
    else
    {
        ui->label_statusPwd->setPixmap(QPixmap(":/ui/image/icon/right.png").
                                       scaled(ui->label_statusPwd->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    }
}

void Register::on_pushButton_finReg_clicked()
{
    Talk_To_Server* phone = new Talk_To_Server(QStringLiteral("ws://112.126.96.244:9999"), this);
}
