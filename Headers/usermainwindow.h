#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

class UserInfor;
namespace Ui {
class UserMainWindow;
}

class UserDetailDlg;

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
    void on_actionUserInfo_triggered();
    void on_ptn_userIcon_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);

private:
    void setStyle();
    void initFriendList();
    void findFriend();

    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;

    bool IsMaxmize = false;
    QRect originalGeometry;

    UserDetailDlg* userIcon;
    QVector<UserInfor>* userData;

    Ui::UserMainWindow *ui;

};

#endif // USERMAINWINDOW_H
