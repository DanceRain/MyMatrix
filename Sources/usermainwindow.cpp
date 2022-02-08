#include "Headers/usermainwindow.h"
#include "ui_usermainwindow.h"
#include "Headers/userdetaildlg.h"
#include <QMouseEvent>
#include <QDebug>

UserMainWindow::UserMainWindow(QWidget *parent, QVector<UserInfor>* currentUserData) :
    QMainWindow(parent),
    userIcon(nullptr),
    userData(currentUserData),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    ui->matrixFriendList->initFriendList(userData);
    this->setStyle();
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->splitter->handle(1)->setDisabled(true);
    QWidget* test = new QWidget(this);
    test->setLayout(ui->vla_nav);
    auto palette = test->palette();
    palette.setColor(QPalette::Window, Qt::blue);
    test->setPalette(palette);
}

UserMainWindow::~UserMainWindow()
{
    delete userData;
    delete ui;
}

void UserMainWindow::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton && IsMaxmize ==  false)
    {
        IsMoving = true;
        mouseStartPoint = e->globalPos();
        qDebug() << mouseStartPoint;
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
    if(userIcon != nullptr)
    {
        delete userIcon;
        userIcon = nullptr;
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

void UserMainWindow::on_ptn_userIcon_clicked()
{
    userIcon = new UserDetailDlg();
    userIcon->move(QCursor::pos());
    userIcon->show();
}
