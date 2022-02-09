#include "Headers/register.h"
#include "ui_register.h"

#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QMouseEvent>
#include <QRegExpValidator>

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
    this->setWindowFlags(Qt::FramelessWindowHint);
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
    Q_UNUSED(arg1);
    QImage img_Judge;
    if(ui->lineEdit_password->text().size() < 8)
    {
        img_Judge = QImage(":/ui/image/icon/wrong.png");
    }
    else if(ui->lineEdit_pwdIdentify->text() != ui->lineEdit_password->text())
    {
        img_Judge = QImage(":/ui/image/icon/wrong.png");

    }
    else
    {
        img_Judge = QImage(":/ui/image/icon/right.png");
    }
    QPixmap pm_Wrong = QPixmap::fromImage(img_Judge);
    ui->label_statusIdtiPwd->setPixmap(pm_Wrong.scaled(ui->label_log->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
}

void Register::on_lineEdit_password_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    QImage img_JudgeSelfStatus;
    QImage img_JudgeIdtiStatus;
    if(ui->lineEdit_password->text().size() < 8)
    {
        img_JudgeSelfStatus = QImage(":/ui/image/icon/wrong.png");
    }
    else
    {
        img_JudgeSelfStatus = QImage(":/ui/image/icon/right.png");
    }

    if(ui->lineEdit_password->text() != ui->lineEdit_pwdIdentify->text())
    {
        img_JudgeIdtiStatus = QImage(":/ui/image/icon/wrong.png");
    }
    else
    {
        img_JudgeIdtiStatus = QImage(":/ui/image/icon/right.png");
    }

    QPixmap pm_JudgeSelfStatus = QPixmap::fromImage(img_JudgeSelfStatus);
    ui->label_statusPwd->setPixmap(pm_JudgeSelfStatus.scaled(ui->label_log->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    QPixmap pm_JudgeIdtiStatus = QPixmap::fromImage(img_JudgeIdtiStatus);
    ui->label_statusIdtiPwd->setPixmap(pm_JudgeIdtiStatus.scaled(ui->label_log->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
}
