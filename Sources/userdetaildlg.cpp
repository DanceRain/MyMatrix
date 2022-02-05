#include "Headers/userdetaildlg.h"
#include "ui_userdetaildlg.h"

UserDetailDlg::UserDetailDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDetailDlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
}

UserDetailDlg::~UserDetailDlg()
{
    delete ui;
}
