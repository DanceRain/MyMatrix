#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Headers/talk_to_server.h"
/*登录界面*/
namespace Ui {
class Dialog;
}

class Dialog : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO ("author", "GuixinWang")
public:
    explicit Dialog(QWidget *parent = nullptr, Talk_To_Server* _Morpheus = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_login_clicked();

signals:
    void registerWindow();
    void userMainWindow();

private:
    void setLog();
    void setStyle();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;
private:
    Talk_To_Server* Morpheus;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
