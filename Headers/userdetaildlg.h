#ifndef USERDETAILDLG_H
#define USERDETAILDLG_H

#include <QWidget>

namespace Ui {
class UserDetailDlg;
}

class UserDetailDlg : public QWidget
{
    Q_OBJECT

public:
    explicit UserDetailDlg(QWidget *parent = nullptr);
    ~UserDetailDlg();

private:
    Ui::UserDetailDlg *ui;
};

#endif // USERDETAILDLG_H
