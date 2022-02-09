#include "Headers/friendlist.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include "Headers/userinfor.h"
#include <QVBoxLayout>

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    m_listWidgetFriends(new QListWidget(this))
{
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    this->setStyleSheet("background:black");
    setListWidgetStyle();
}

void FriendList::initFriendList(QVector<UserInfor>* recentContacts)
{
    if(recentContacts == nullptr)
    {
        return;
    }
    /*登录界面*/
    for (int i = 0; i < recentContacts->size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(300, 80));
        m_listWidgetFriends->addItem(item);

        QWidget *pItemWidget = new QWidget(m_listWidgetFriends);
        QLabel* nickName = new QLabel(recentContacts->at(i).getSNickName());
        QLabel* recentMessage = new QLabel(recentContacts->at(i).getVRecentMessage()[0]);
        QLabel* userIcon = new QLabel();
        userIcon->setPixmap(QPixmap(":/ui/image/icon/log.png").scaled(userIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QHBoxLayout* hla = new QHBoxLayout;
        hla->addWidget(nickName);
        hla->addWidget(userIcon);
        hla->addWidget(recentMessage);
        pItemWidget->setLayout(hla);

        m_listWidgetFriends->setItemWidget(item, pItemWidget);
    }
    m_listWidgetFriends->setCurrentRow(0);
    QVBoxLayout* box = new QVBoxLayout();
    box->addWidget(m_listWidgetFriends);
}

FriendList::~FriendList()
{
    delete m_listWidgetFriends;
}

void FriendList::setListWidgetStyle()
{
    m_listWidgetFriends->setMinimumWidth(300);
//    m_listWidgetFriends->setMinimumHeight(600);
    m_listWidgetFriends->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

