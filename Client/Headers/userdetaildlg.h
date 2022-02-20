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

public:
    void setUseIcon(const QPixmap& pix_UserIcon);
    void setUserName(const QString& s_UserName);
    void setUserGender(const QPixmap& pix_UserGender);
    void setUserNote(const QString& s_UserNote);
    void setUserCallNumber(const QString& s_UserCallNumber);
    void setUserArea(const QString& s_UserArea);


private:
    void setStyle();
    Ui::UserDetailDlg *ui;
};

#endif // USERDETAILDLG_H
