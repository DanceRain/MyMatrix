#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <QVector>

class QListWidget;
class UserInfor;

//FriendList是一个联系人列表类，他接收新信息并更新其中包含的Widget
class FriendList : public QWidget
{
    Q_OBJECT
public:
    explicit FriendList(QWidget *parent = nullptr);
    void initFriendList(QVector<UserInfor>* recentContacts);
    ~FriendList();

signals:

public slots:

//FriendList初始化
private:
    void initList();
private:
    QListWidget *m_listWidgetFriends;
};

#endif // FRIENDLIST_H
