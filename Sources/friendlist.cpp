#include "Headers/friendlist.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include "Headers/userinfor.h"


FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    m_listWidgetFriends(new QListWidget(this))
{

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
        item->setSizeHint(QSize(10, 65));
        m_listWidgetFriends->addItem(item);

        QWidget *pItemWidget = new QWidget(m_listWidgetFriends);
        QLabel* nickName = new QLabel(recentContacts->at(i).getSNickName());
        QPushButton* userIcon = new QPushButton();
        userIcon->setIcon(QPixmap(":/ui/image/icon/log.png"));
        QLabel* recentMessage = new QLabel(recentContacts->at(i).getVRecentMessage()[0]);
        QHBoxLayout* hla = new QHBoxLayout;
        hla->addWidget(nickName);
        hla->addWidget(userIcon);
        hla->addWidget(recentMessage);
        pItemWidget->setLayout(hla);

        m_listWidgetFriends->setItemWidget(item, pItemWidget);
    }
    m_listWidgetFriends->setCurrentRow(0);
}

FriendList::~FriendList()
{
    delete m_listWidgetFriends;
}

void FriendList::initList()
{

}
