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
#include <QGraphicsDropShadowEffect>


UserMainWindow::UserMainWindow(QWidget *parent, QVector<UserInfor>* currentm_UserData) :
    QMainWindow(parent),
    m_UserDetailDlg(nullptr),
    m_UserData(currentm_UserData),
    m_UserDataModel(new QStandardItemModel(this)),
    m_UserDataProxyModel(new QSortFilterProxyModel(this)),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    initFriendView();
    setStyle();
}

UserMainWindow::~UserMainWindow()
{
    delete m_UserData;
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
    if(m_UserDetailDlg != nullptr)
    {
        delete m_UserDetailDlg;
        m_UserDetailDlg = nullptr;
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
    this->setWindowFlag(Qt::FramelessWindowHint);
}

void UserMainWindow::initFriendView()
{
    for(int i = 0; i < m_UserData->size(); ++i)
    {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.userName = m_UserData->at(i).getSNickName();
        itemData.icon = m_UserData->at(i).getPixUserIcon();
        itemData.recentMessage = m_UserData->at(i).getVRecentMessage()[0];
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pItem->setData(m_UserData->at(i).getSNickName(), Qt::UserRole);
        m_UserDataModel->appendRow(pItem);
    }
    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);

    m_UserDataProxyModel->setSourceModel(m_UserDataModel);
    m_UserDataProxyModel->setFilterRole(Qt::UserRole);
    ui->listView_matrix->setItemDelegate(pItemDelegate);
    ui->listView_matrix->setModel(m_UserDataProxyModel);
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

void UserMainWindow::on_ptn_userIcon_clicked()
{
    m_UserDetailDlg = new UserDetailDlg(this);
    m_UserDetailDlg->setUseIcon(m_UserData->at(0).getPixUserIcon());
    m_UserDetailDlg->setUserName(m_UserData->at(0).getSNickName());
    m_UserDetailDlg->setUserArea(m_UserData->at(0).getSUserArea());
    m_UserDetailDlg->setUserGender(m_UserData->at(0).getPixUserGender());
    m_UserDetailDlg->setUserNote(m_UserData->at(0).getSUserNote());
    m_UserDetailDlg->setUserCallNumber(m_UserData->at(0).getSUserNumber());

    m_UserDetailDlg->move(QCursor::pos() - this->pos());
    m_UserDetailDlg->show();
}

void UserMainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    qDebug() << arg1;
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::RegExp);
    m_UserDataProxyModel->setFilterRegExp(regExp);
}
