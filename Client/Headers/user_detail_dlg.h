#ifndef USER_DETAIL_DLG_H
#define USER_DETAIL_DLG_H

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
    void setUserName(const QString& s_UserName);
    QString getUserName() const;

    void setUserIcon(const QPixmap& pix_UserIcon);
    QPixmap getUserIcon() const;

    void setUserGender(const QPixmap& pix_UserGender);

    void setUserNote(const QString& s_UserNote);
    void setUserCallNumber(const QString& s_UserCallNumber);
    void setUserArea(const QString& s_UserArea);

protected:
    void paintEvent(QPaintEvent* event);


private:
    void setStyle();
    Ui::UserDetailDlg *ui;
};

#endif // USER_DETAIL_DLG_H
