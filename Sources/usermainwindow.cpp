#include "Headers/usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include "Headers/userinfor.h"
#include "Headers/userdetaildlg.h"

UserMainWindow::UserMainWindow(QWidget *parent, QVector<UserInfor>* currentUserData) :
    QMainWindow(parent),
    userIcon(nullptr),
    userData(currentUserData),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    initFriendList();
//    ui->splitter->setStretchFactor(0, 0);
//    ui->splitter->setStretchFactor(0, 1);
//    ui->matrixFriendList->initFriendList(userData);
//    ui->matrixFriendList->setStyleSheet("background:black");
//    ui->matrixFriendList->setMinimumSize(QSize(300, 30));
//    qDebug() << ui->matrixFriendList->size();
    this->setStyle();
    this->setWindowFlag(Qt::FramelessWindowHint);
    //使鼠标在splitter上不再显示分隔符
//    ui->splitter->handle(1)->setDisabled(true);
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

//初始化好友信息
void UserMainWindow::initFriendList()
{
    if(userData == nullptr)
    {
        return;
    }
    /*登录界面*/
    for (int i = 0; i < userData->size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText("王桂鑫");
        item->setSizeHint(QSize(295, 80));
        ui->listWidget_matrix->addItem(item);

        QWidget *pItemWidget = new QWidget(ui->listWidget_matrix);
        QLabel* nickName = new QLabel(userData->at(i).getSNickName());
        QLabel* recentMessage = new QLabel(userData->at(i).getVRecentMessage()[0]);
        QVBoxLayout* vlaNameAndMsg = new QVBoxLayout();
        vlaNameAndMsg->addWidget(nickName);
        vlaNameAndMsg->addWidget(recentMessage);
        QHBoxLayout* hlaUserProfile = new QHBoxLayout();
        QLabel* userIcon = new QLabel();
        userIcon->setFixedSize(QSize(60, 60));
        userIcon->setPixmap(QPixmap(userData->at(i).getPixUserIcon()).scaled(userIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        hlaUserProfile->addWidget(userIcon);
        hlaUserProfile->addLayout(vlaNameAndMsg);
        pItemWidget->setLayout(hlaUserProfile);
        ui->listWidget_matrix->setItemWidget(item, pItemWidget);
    }
    ui->listWidget_matrix->setCurrentRow(0);
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
        IsMaxmize = false;
        //当窗口放大时，使窗口不能够移动
        IsMoving = false;
    }
    else {
        IsMaxmize = true;
        this->showMaximized();
//        ui->matrixFriendList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
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

void UserMainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    qDebug() << arg1;

    qDebug() << ui->listWidget_matrix->findItems(arg1, 0);
}
