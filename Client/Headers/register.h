#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

/*注册界面*/
namespace Ui {
class Register;
}

class Talk_To_Server;

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *lastWindow = nullptr, QWidget *parent = nullptr, Talk_To_Server* _Morpheus = nullptr);
    ~Register();

private slots:
    void on_pushButton_shutdown_clicked();
    void on_pushButton_minimize_clicked();
    void on_pushButton_back_clicked();
    void on_lineEdit_pwdIdentify_textChanged(const QString &arg1);
    void on_lineEdit_password_textChanged(const QString &arg1);
    void on_pushButton_finReg_clicked();
    void on_lineEdit_account_textChanged(const QString &arg1);
    void inforUserNewId(const QString& new_id);

    void on_lineEdit_userName_textChanged(const QString &arg1);

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
    void setLog();
    void setStyle();
    void setLineEditValidator();

private:
    Talk_To_Server* Morpheus;
    QWidget* widget_lastWindow;
    Ui::Register *ui;
};

#endif // REGISTER_H
