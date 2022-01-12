/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton_login;
    QPushButton *pushButton_register;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_log;
    QLabel *label_name;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_account;
    QLineEdit *lineEdit_password;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_shutdown;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *cbx_remPw;
    QCheckBox *cbx_autoLogin;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(350, 400);
        Dialog->setMinimumSize(QSize(350, 400));
        Dialog->setMaximumSize(QSize(350, 400));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ui/image/icon/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        Dialog->setStyleSheet(QString::fromUtf8(""));
        pushButton_login = new QPushButton(Dialog);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(60, 260, 230, 50));
        pushButton_login->setMinimumSize(QSize(230, 50));
        pushButton_login->setMaximumSize(QSize(230, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        pushButton_login->setFont(font);
        pushButton_register = new QPushButton(Dialog);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(20, 340, 93, 28));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        pushButton_register->setFont(font1);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 151, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_log = new QLabel(layoutWidget);
        label_log->setObjectName(QString::fromUtf8("label_log"));
        label_log->setMinimumSize(QSize(0, 0));
        label_log->setMaximumSize(QSize(10000, 100));
        label_log->setLayoutDirection(Qt::LeftToRight);
        label_log->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_log);

        label_name = new QLabel(layoutWidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setMinimumSize(QSize(100, 30));
        label_name->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(15);
        label_name->setFont(font2);
        label_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_name);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 70, 281, 141));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_account = new QLineEdit(layoutWidget1);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));
        lineEdit_account->setMinimumSize(QSize(0, 30));
        lineEdit_account->setFont(font1);

        verticalLayout->addWidget(lineEdit_account);

        lineEdit_password = new QLineEdit(layoutWidget1);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMinimumSize(QSize(0, 30));
        lineEdit_password->setFont(font1);
        lineEdit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_password);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(240, 0, 126, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, 0, 20, 0);
        pushButton_minimize = new QPushButton(layoutWidget2);
        pushButton_minimize->setObjectName(QString::fromUtf8("pushButton_minimize"));
        pushButton_minimize->setMinimumSize(QSize(30, 30));
        pushButton_minimize->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton_minimize);

        pushButton_shutdown = new QPushButton(layoutWidget2);
        pushButton_shutdown->setObjectName(QString::fromUtf8("pushButton_shutdown"));
        pushButton_shutdown->setMinimumSize(QSize(30, 30));
        pushButton_shutdown->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton_shutdown);

        layoutWidget3 = new QWidget(Dialog);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(80, 220, 201, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        cbx_remPw = new QCheckBox(layoutWidget3);
        cbx_remPw->setObjectName(QString::fromUtf8("cbx_remPw"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(8);
        cbx_remPw->setFont(font3);

        horizontalLayout_3->addWidget(cbx_remPw);

        cbx_autoLogin = new QCheckBox(layoutWidget3);
        cbx_autoLogin->setObjectName(QString::fromUtf8("cbx_autoLogin"));
        cbx_autoLogin->setFont(font3);

        horizontalLayout_3->addWidget(cbx_autoLogin);


        retranslateUi(Dialog);
        QObject::connect(pushButton_minimize, SIGNAL(clicked()), Dialog, SLOT(showMinimized()));
        QObject::connect(pushButton_shutdown, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Dialog", "\347\231\273\345\275\225", nullptr));
        pushButton_register->setText(QCoreApplication::translate("Dialog", "\346\263\250\345\206\214", nullptr));
        label_log->setText(QString());
        label_name->setText(QCoreApplication::translate("Dialog", "Matrix", nullptr));
        lineEdit_account->setPlaceholderText(QCoreApplication::translate("Dialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("Dialog", "\345\257\206\347\240\201", nullptr));
        pushButton_minimize->setText(QString());
        pushButton_shutdown->setText(QString());
        cbx_remPw->setText(QCoreApplication::translate("Dialog", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        cbx_autoLogin->setText(QCoreApplication::translate("Dialog", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
