﻿#ifndef DIALOG_H
#define DIALOG_H

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
    explicit Dialog(Talk_To_Server* _deliver = nullptr, QWidget *parent = nullptr);
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

private:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;
private:
    Talk_To_Server* m_deliver;
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
