#include "Headers/usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QMouseEvent>
#include <QDebug>

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    this->setStyle();
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->splitter->handle(1)->setDisabled(true);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton && IsMaxmize ==  false)
    {
        IsMoving = true;
        mouseStartPoint = e->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void UserMainWindow::mouseMoveEvent(QMouseEvent* e)
{
    if(IsMoving)
    {
        QPoint distance = e->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void UserMainWindow::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        IsMoving = false;
    }
}

void UserMainWindow::dragEnterEvent(QDragEnterEvent* event)
{
}

void UserMainWindow::dropEvent(QDropEvent* event)
{

}

void UserMainWindow::setStyle()
{
    QString qss;
    QFile qssFile(":/qss/userMainWindow.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
}

void UserMainWindow::on_pushButton_maxmize_clicked()
{
    if(IsMaxmize == true)
    {
        this->showNormal();
//        this->setGeometry(originalGeometry);
        IsMaxmize = false;
        qDebug() << "set Original";
        IsMoving = false;
    }
    else {
        qDebug() << "set Max";
        IsMaxmize = true;
        this->showMaximized();
    }
}

void UserMainWindow::on_actionUserInfo_triggered()
{
    QWidget* UserInfor = new QWidget();
    UserInfor->show();
}
