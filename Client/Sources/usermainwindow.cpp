#include "Headers/userinfor.h"
#include "Headers/userdetaildlg.h"
#include "Headers/MuItemDelegate.h"
#include "Headers/MuListItemData.h"
#include "Headers/usermainwindow.h"
#include "Headers/ChatItemBase.h"
#include "Headers/TextBubble.h"
#include "Headers/ChatView.h"
#include "ui_usermainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QDebug>
#include <QSortFilterProxyModel>



UserMainWindow::UserMainWindow(QWidget *parent, QVector<UserInfor>* currentm_UserData) :
    QMainWindow(parent),
    m_UserDetailDlg(nullptr),
    m_UserData(currentm_UserData),
    m_UserDataModel(new QStandardItemModel(this)),
    m_UserDataProxyModel(new QSortFilterProxyModel(this)),
    m_ItemDelegate(new MuItemDelegate(this)),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    initFriendsView();
    initContactsView();
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

void UserMainWindow::paintEvent(QPaintEvent* event)
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

void UserMainWindow::initContactsView()
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
    ui->listView_recentContacts->setItemDelegate(pItemDelegate);
    ui->listView_recentContacts->setModel(m_UserDataProxyModel);
    ui->treeView_friendsList->hide();
}

void UserMainWindow::initFriendsView()
{
    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    ui->treeView_friendsList->setItemDelegate(pItemDelegate);
    ui->treeView_friendsList->setModel(m_UserDataProxyModel);
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

void UserMainWindow::on_ptn_friendList_clicked()
{
    ui->treeView_friendsList->show();
    ui->listView_recentContacts->hide();
}

void UserMainWindow::on_ptn_message_clicked()
{
    ui->listView_recentContacts->show();
    ui->treeView_friendsList->hide();
}

void UserMainWindow::on_ptn_sendMessage_clicked()
{
    MessageTextEdit *pTextEdit = ui->ted_editArea;
    ChatRole role = ChatRole::Self;
    QString userName = QStringLiteral("张荆");

    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i=0; i<msgList.size(); ++i)
    {
        QString type = msgList[i].msgFlag;
        ChatItemBase *pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(":/ui/image/icon/log.png"));
        QWidget *pBubble = nullptr;
        if(type == "text")
        {
            pBubble = new TextBubble(role, msgList[i].content);
        }
        else if(type == "image")
        {
//            pBubble = new PictureBubble(QPixmap(msgList[i].content) , role);
        }
        else if(type == "file")
        {

        }
        if(pBubble != nullptr)
        {
            pChatItem->setWidget(pBubble);
            ui->wdt_inforArea->appendChatItem(pChatItem);
        }
    }
}
