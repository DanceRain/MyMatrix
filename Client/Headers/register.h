#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "Headers/talk_to_server.h"
/*注册界面*/
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(Talk_To_Server* _deliver = nullptr, QWidget *lastWindow = nullptr, QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_shutdown_clicked();

    void on_pushButton_minimize_clicked();

    void on_pushButton_back_clicked();

    void on_lineEdit_pwdIdentify_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);

    void on_pushButton_finReg_clicked();

private:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;

private:
    void setLog();
    void setStyle();
    void setLineEditValidator();
private:
    Talk_To_Server* m_deliver;
private:
    QWidget* widget_lastWindow;
    Ui::Register *ui;
};

#endif // REGISTER_H
