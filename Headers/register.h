#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr, QWidget *lastWindow = nullptr);
    ~Register();

private slots:
    void on_pushButton_shutdown_clicked();

    void on_pushButton_minimize_clicked();

    void on_pushButton_back_clicked();

    void on_lineEdit_pwdIdentify_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);

private:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    void setLog();
    void setStyle();
    void setLineEditValidator();

    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;

    QWidget* widget_lastWindow;
    Ui::Register *ui;

};

#endif // REGISTER_H
