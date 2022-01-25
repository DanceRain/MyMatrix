#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    Q_CLASSINFO ("author", "GuixinWang")
public:
    explicit Dialog(QWidget *parent = nullptr);
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

    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    bool IsMoving = false;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
