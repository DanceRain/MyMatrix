#include "Headers/userinfor.h"
#include "Headers/userdetaildlg.h"
#include "Headers/MuItemDelegate.h"
#include "Headers/MuListItemData.h"
#include "Headers/usermainwindow.h"

#include "ui_usermainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QDebug>
#include <QSortFilterProxyModel>


UserMainWindow::UserMainWindow(QWidget *parent, QVector<UserInfor>* currentUserData) :
    QMainWindow(parent),
    userIcon(nullptr),
    userData(currentUserData),
    userDataModel(new QStandardItemModel(this)),
    userDataProxyModel(new QSortFilterProxyModel(this)),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    initFriendView();
    this->setStyle();
    this->setWindowFlag(Qt::FramelessWindowHint);
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

void UserMainWindow::initFriendView()
{
    for(int i = 0; i < userData->size(); ++i)
    {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.userName = userData->at(i).getSNickName();
        itemData.icon = userData->at(i).getPixUserIcon();
        itemData.recentMessage = userData->at(i).getVRecentMessage()[0];
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pItem->setData(userData->at(i).getSNickName(), Qt::UserRole);
        userDataModel->appendRow(pItem);
    }
    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);

    userDataProxyModel->setSourceModel(userDataModel);
    userDataProxyModel->setFilterRole(Qt::UserRole);
    ui->listView_matrix->setItemDelegate(pItemDelegate);
    ui->listView_matrix->setModel(userDataProxyModel);
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
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::RegExp);
    userDataProxyModel->setFilterRegExp(regExp);
}
