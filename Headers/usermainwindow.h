#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserMainWindow;
}

class UserDetailDlg;

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();
protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private slots:
    void on_pushButton_maxmize_clicked();

    void on_actionUserInfo_triggered();

    void on_ptn_userIcon_clicked();

private:
    void setStyle();

    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;

    bool IsMaxmize = false;
    QRect originalGeometry;

    UserDetailDlg* userIcon;
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
