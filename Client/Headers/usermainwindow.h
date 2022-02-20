#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

class UserInfor;
class UserDetailDlg;
class QStandardItemModel;
class QSortFilterProxyModel;
class MuItemDelegate;

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr, QVector<UserInfor>* currentUserData = nullptr);
    ~UserMainWindow();
protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private slots:
    void on_pushButton_maxmize_clicked();
    void on_ptn_userIcon_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_ptn_friendList_clicked();

    void on_ptn_message_clicked();

private:
    void setStyle();
    void initContactsView();
    void initFriendsView();
//    void initFriendList();
    void findFriend();
private:
    //用于窗口移动和缩放
    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;
    bool IsMaxmize = false;
private:
    //用于窗口信息初始化
    UserDetailDlg* m_UserDetailDlg;
    QVector<UserInfor>* m_UserData;
    QStandardItemModel* m_UserDataModel;
    QSortFilterProxyModel* m_UserDataProxyModel;
    MuItemDelegate* m_ItemDelegate;
private:
    Ui::UserMainWindow* ui;
};

#endif // USERMAINWINDOW_H
