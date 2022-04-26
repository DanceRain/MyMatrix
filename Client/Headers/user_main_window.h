#ifndef USER_MAINWINDOW_H
#define USER_MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>

class UserInfor;
class UserDetailDlg;
class QStandardItemModel;
class QSortFilterProxyModel;
class MuItemDelegate;
class Talk_To_Server;

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QString _user_account, QWidget *parent = nullptr, Talk_To_Server* Morpheus = nullptr);
    ~UserMainWindow();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private slots:
    void on_pushButton_maxmize_clicked();
    void on_ptn_userIcon_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_ptn_friendList_clicked();
    void on_ptn_message_clicked();
    void on_ptn_sendMessage_clicked();
    void on_pushButton_addFriend_clicked();
private slots:
    void getMessage(QJsonObject& message);

private:
    void setStyle();
    void initContactsView();
    void initFriendsView();
    void initMainWindowLayout();
    void initUserDetail();
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
    QStandardItemModel* m_UserDataModel;
    QSortFilterProxyModel* m_UserDataProxyModel;
    MuItemDelegate* m_ItemDelegate;
private:
    QString userAccount;
    Talk_To_Server* Morpheus;
    Ui::UserMainWindow* ui;
};

#endif //USER_MAINWINDOW_H
