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
#include "Headers/local_msg.h"
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
#include <QModelIndex>

UserMainWindow::UserMainWindow(const QString& _user_account, QWidget* parent, Talk_To_Server* _Morpheus) :
    QMainWindow(parent),
    m_UserDetailDlg(nullptr),
    m_UserDataModel(new QStandardItemModel(this)),
    m_UserDataProxyModel(new QSortFilterProxyModel(this)),
    m_ItemDelegate(new MuItemDelegate(this)),
    userAccount(std::move(_user_account)),
    Morpheus(_Morpheus),
    dbController(_user_account, "123456"),
    ui(new Ui::UserMainWindow)
{
    qDebug() << "this is _use_account" << _user_account << endl;
    ui->setupUi(this);
    initMainWindowLayout();
    initUserDetail();
    //initFriendsView();
    //initContactsView();
    setStyle();
    Morpheus->startTalkInWs(this->userAccount);
    connect(Morpheus, &Talk_To_Server::receivedMessage, this, &UserMainWindow::getMessage);
    connect(ui->listView_recentContacts, &QListView::clicked, this, &UserMainWindow::on_listViewitem_clicked);
    connect(ui->ted_editArea, &MessageTextEdit::send, this, &UserMainWindow::on_ptn_sendMessage_clicked);
}

UserMainWindow::~UserMainWindow()
{
    Morpheus = nullptr;
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
    this->resize(1000, 610);
};

void UserMainWindow::initUserDetail()
{
    QJsonObject ret = Morpheus->m_requestUserInfor(userAccount);
    m_UserDetailDlg = new UserDetailDlg(this);
    m_UserDetailDlg->setUserCallNumber(QString::number(ret["user_detail"].toObject()["user_account"].toInt()));
    m_UserDetailDlg->setUserIcon(QPixmap(":/ui/image/icon/log.png"));
    m_UserDetailDlg->setUserName(ret["user_detail"].toObject()["user_name"].toString());
    m_UserDetailDlg->setUserArea(ret["user_detail"].toObject()["user_area"].toString());
    if(ret["user_detail"].toObject()["user_gender"].toInt() == 0)
    {
        m_UserDetailDlg->setUserGender(QPixmap(":/ui/image/icon/famale.jpg"));
    }
    else
    {
        m_UserDetailDlg->setUserGender(QPixmap(":/ui/image/icon/male.jpg"));
    }
    m_UserDetailDlg->hide();

    for(int i = 1; i < ret.count(); ++i)
    {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.userAccount = ret["friend " + QString::number(i)].toObject()["user_account"].toInt();
        itemData.userName = ret["friend " + QString::number(i)].toObject()["user_name"].toString();
        itemData.icon = QPixmap(":/ui/image/icon/log.png");
        itemData.recentMessage = "Hello, I'm " + itemData.userName;
        itemData.userGender = ret["friend " + QString::number(i)].toObject()["user_gender"].toInt();
        itemData.userArea = ret["friend " + QString::number(i)].toObject()["user_area"].toString();
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pItem->setData(itemData.userName, Qt::UserRole);
        m_UserDataModel->appendRow(pItem);
    }
    MuItemDelegate* pItemDelegate = new MuItemDelegate(this);
    m_UserDataProxyModel->setSourceModel(m_UserDataModel);
    m_UserDataProxyModel->setFilterRole(Qt::UserRole);
    ui->listView_recentContacts->setItemDelegate(pItemDelegate);
    ui->listView_recentContacts->setModel(m_UserDataProxyModel);
}

void UserMainWindow::initUserdMessage(int friend_id)
{
    auto ret = dbController.selectMessage(friend_id);
    ui->wdt_inforArea->clearItem();
    on_read_chatRecord(ret);
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
    ChatRole role = ChatRole::Self;
    MessageTextEdit* pTextEdit = ui->ted_editArea;
    QString userName;

    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i=0; i<msgList.size(); ++i)
    {
        QString type = msgList[i].msgFlag;
        ChatItemBase* pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(m_UserDetailDlg->getUserIcon());
        QWidget* pBubble = nullptr;
        if(type == "text")
        {
            pBubble = new TextBubble(role, msgList[i].content);
            dbController.insertMessage(curSelectFriendIdx.data(Qt::UserRole + 1).value<MuItemData>().userAccount, msgList[i].content, 0);
            Morpheus->m_sendMessage(userAccount, QString::number(curSelectFriendIdx.data(Qt::UserRole + 1).value<MuItemData>().userAccount), msgList[i].content);
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
 * 6 接受成为好友请求
 * 7 拒绝成为好友请求
 * 8 用户消息
 * 9 用户登录确认
 */
void UserMainWindow::getMessage(QJsonObject& message)
{
    switch (message["content_type"].toInt())
    {
        case 4:
        {
            QMessageBox::StandardButton box;
            box = QMessageBox::question(this, "A new friend request.",
                            QString::number(message["infor_sender"].toInt()) + " want to be your friend.",
                    QMessageBox::Yes | QMessageBox::No);
            if(box == QMessageBox::No)
            {
                Morpheus->m_responseAddFriend(false, QString::number(message["infor_sender"].toInt()));
            }
            else
            {
                Morpheus->m_responseAddFriend(true, QString::number(message["infor_sender"].toInt()));
            }
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
            QMessageBox::information(nullptr, "A new friend", QString::number(message["infor_sender"].toString().toInt()) + " agree to be your friend.");
            break;
        }
        case 7:
        {
            QMessageBox::information(nullptr, "Request response", QString::number(message["infor_sender"].toString().toInt()) + " don't agree to be your friend.");
            break;
        }
        case 8:
        {
            if(curSelectFriendIdx.data(Qt::UserRole + 1).value<MuItemData>().userAccount == message["infor_sender"].toString().toInt())
            {
                ChatItemBase* pChatItem;
                QWidget* pBubble;
                pChatItem = new ChatItemBase(ChatRole::Other);
                pChatItem->setUserName(ui->label_inforAreaName->text());
                pChatItem->setUserIcon(curSelectFriendIdx.data(Qt::UserRole + 1).value<MuItemData>().icon);
                pBubble = new TextBubble(ChatRole::Other, message["infor_content"].toString());
                if(pBubble != nullptr)
                {
                    pChatItem->setWidget(pBubble);
                    ui->wdt_inforArea->appendChatItem(pChatItem);
                }
            }
            dbController.insertMessage(message["infor_sender"].toString().toInt(), message["infor_content"].toString(), 1);
            break;
        }
        case 10:
        {
            Morpheus->closeWs();
            this->close();
            break;
        }
        default:
        {

        }
    }
}

void UserMainWindow::on_pushButton_shutdown_clicked()
{
    Morpheus->m_quit();
}

void UserMainWindow::on_listViewitem_clicked(const QModelIndex& idx)
{
    curSelectFriendIdx = idx;
    MuItemData data = idx.data(Qt::UserRole + 1).value<MuItemData>();
    ui->label_inforAreaName->setText(data.userName);

    initUserdMessage(data.userAccount);
}

void UserMainWindow::on_read_chatRecord(const QVector<LocalMsg>& vecMsg)
{
    if(vecMsg.empty())
    {
        return;
    }
    for(auto msg : vecMsg)
    {
        ChatItemBase* pChatItem;
        QWidget* pBubble;
        if(msg.getMsgType() == 0)
        {
            pChatItem = new ChatItemBase(ChatRole::Self);
            pChatItem->setUserName(m_UserDetailDlg->getUserName());
            pChatItem->setUserIcon(m_UserDetailDlg->getUserIcon());
            pBubble = new TextBubble(ChatRole::Self, msg.getMsgContent());

        }
        else
        {
            pChatItem = new ChatItemBase(ChatRole::Other);
            pChatItem->setUserName(ui->label_inforAreaName->text());
            pChatItem->setUserIcon(curSelectFriendIdx.data(Qt::UserRole + 1).value<MuItemData>().icon);
            pBubble = new TextBubble(ChatRole::Other, msg.getMsgContent());
        }
        if(pBubble != nullptr)
        {
            pChatItem->setWidget(pBubble);
            ui->wdt_inforArea->appendChatItem(pChatItem);
        }
    }
}
