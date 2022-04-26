#include "Headers/userinfor.h"
#include "Headers/user_detail_dlg.h"
#include "Headers/mult_item_delegate.h"
#include "Headers/mult_item_data.h"
#include "Headers/user_main_window.h"
#include "Headers/chat_item_base.h"
#include "Headers/text_bubble.h"
#include "Headers/chat_view.h"
#include "Headers/picture_bubble.h"
#include "Headers/talk_to_server.h"
#include "ui_usermainwindow.h"

#include <QStandardItem>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>
#include <iostream>

UserMainWindow::UserMainWindow(QString _user_account, QWidget* parent, Talk_To_Server* _Morpheus) :
    QMainWindow(parent),
    m_UserDetailDlg(nullptr),
    m_UserDataModel(new QStandardItemModel(this)),
    m_UserDataProxyModel(new QSortFilterProxyModel(this)),
    m_ItemDelegate(new MuItemDelegate(this)),
    userAccount(std::move(_user_account)),
    Morpheus(_Morpheus),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    initMainWindowLayout();
    initUserDetail();
    //initFriendsView();
    initContactsView();
    setStyle();
    Morpheus->startTalkInWs(this->userAccount);
    connect(Morpheus, &Talk_To_Server::receivedMessage, this, &UserMainWindow::getMessage);
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
        qDebug() << mouseStartPoint;
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
    if(!m_UserDetailDlg->isHidden())
    {
        m_UserDetailDlg->hide();
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
    {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.userName = "Neo";
        itemData.icon = QPixmap(":/ui/image/icon/log.png");
        itemData.recentMessage = "";
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pItem->setData("Neo", Qt::UserRole);
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

void UserMainWindow::initMainWindowLayout()
{
    ui->wdt_userDetail->hide();
    ui->treeView_friendsList->hide();
}

void UserMainWindow::initUserDetail()
{
    QJsonObject ret = Morpheus->m_requestUserInfor(userAccount);
    m_UserDetailDlg = new UserDetailDlg(this);
    m_UserDetailDlg->setUserCallNumber(ret["user_name"].toString());
    m_UserDetailDlg->hide();
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
            pBubble = new PictureBubble(QPixmap(msgList[i].content) , role);
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

void UserMainWindow::on_pushButton_addFriend_clicked()
{
    bool isOk;
    QString friend_id = QInputDialog::getText(nullptr, "Find friend",
                                         "Please input your friend's ID.",
                                         QLineEdit::Normal, "Id", &isOk);
    if(isOk)
    {
        Morpheus->m_addFriend(friend_id, userAccount);
    }
}

/*content-type:
 * 1 注册
 * 2 登录
 * 3 获取用户个人信息，包括好友列表初始化信息
 * 4 请求添加好友信息
 * 5 请求添加好友信息回复(判断请求账号是否有效)
 * 6 用户消息
 */
void UserMainWindow::getMessage(QJsonObject& message)
{
    switch (message["content_type"].toInt())
    {
        case 4:
        {
            break;
        }
        case 5:
        {
            if(message["is_exist"].toBool())
            {
                QMessageBox::information(nullptr, "Information", "Your request has been sent.");
            }
            else
            {
                QMessageBox::information(nullptr, "Information", "The account is not exist, please check.");
            }
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        default:
        {

        }
    }
}
