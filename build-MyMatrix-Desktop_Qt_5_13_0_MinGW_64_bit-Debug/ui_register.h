/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_account;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_pwdIdentify;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_shutdown;
    QPushButton *pushButton_back;
    QPushButton *pushButton_finReg;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_log;
    QLabel *label_name;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_statusUser;
    QLabel *label_statusPwd;
    QLabel *label_statusIdtiPwd;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(400, 425);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ui/image/icon/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        Register->setWindowIcon(icon);
        layoutWidget = new QWidget(Register);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 50, 281, 251));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_account = new QLineEdit(layoutWidget);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));
        lineEdit_account->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        lineEdit_account->setFont(font);

        verticalLayout->addWidget(lineEdit_account);

        lineEdit_password = new QLineEdit(layoutWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMinimumSize(QSize(0, 30));
        lineEdit_password->setFont(font);
        lineEdit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_password);

        lineEdit_pwdIdentify = new QLineEdit(layoutWidget);
        lineEdit_pwdIdentify->setObjectName(QString::fromUtf8("lineEdit_pwdIdentify"));
        lineEdit_pwdIdentify->setMinimumSize(QSize(0, 30));
        lineEdit_pwdIdentify->setFont(font);
        lineEdit_pwdIdentify->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_pwdIdentify);

        layoutWidget_2 = new QWidget(Register);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(280, 0, 126, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, 0, 20, 0);
        pushButton_minimize = new QPushButton(layoutWidget_2);
        pushButton_minimize->setObjectName(QString::fromUtf8("pushButton_minimize"));
        pushButton_minimize->setMinimumSize(QSize(30, 30));
        pushButton_minimize->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton_minimize);

        pushButton_shutdown = new QPushButton(layoutWidget_2);
        pushButton_shutdown->setObjectName(QString::fromUtf8("pushButton_shutdown"));
        pushButton_shutdown->setMinimumSize(QSize(30, 30));
        pushButton_shutdown->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton_shutdown);

        pushButton_back = new QPushButton(Register);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setGeometry(QRect(10, 370, 93, 28));
        pushButton_back->setFont(font);
        pushButton_finReg = new QPushButton(Register);
        pushButton_finReg->setObjectName(QString::fromUtf8("pushButton_finReg"));
        pushButton_finReg->setGeometry(QRect(110, 310, 161, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pushButton_finReg->setFont(font1);
        layoutWidget_3 = new QWidget(Register);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 0, 151, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_log = new QLabel(layoutWidget_3);
        label_log->setObjectName(QString::fromUtf8("label_log"));
        label_log->setMinimumSize(QSize(0, 0));
        label_log->setMaximumSize(QSize(10000, 100));
        label_log->setLayoutDirection(Qt::LeftToRight);
        label_log->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_log);

        label_name = new QLabel(layoutWidget_3);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setMinimumSize(QSize(100, 30));
        label_name->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(15);
        label_name->setFont(font2);
        label_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_name);

        widget = new QWidget(Register);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(340, 70, 41, 211));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_statusUser = new QLabel(widget);
        label_statusUser->setObjectName(QString::fromUtf8("label_statusUser"));

        verticalLayout_2->addWidget(label_statusUser);

        label_statusPwd = new QLabel(widget);
        label_statusPwd->setObjectName(QString::fromUtf8("label_statusPwd"));

        verticalLayout_2->addWidget(label_statusPwd);

        label_statusIdtiPwd = new QLabel(widget);
        label_statusIdtiPwd->setObjectName(QString::fromUtf8("label_statusIdtiPwd"));

        verticalLayout_2->addWidget(label_statusIdtiPwd);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        lineEdit_account->setPlaceholderText(QCoreApplication::translate("Register", "\347\224\250\346\210\267\345\220\215", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("Register", "\345\257\206\347\240\201", nullptr));
        lineEdit_pwdIdentify->setPlaceholderText(QCoreApplication::translate("Register", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        pushButton_minimize->setText(QString());
        pushButton_shutdown->setText(QString());
        pushButton_back->setText(QCoreApplication::translate("Register", "\350\277\224\345\233\236", nullptr));
        pushButton_finReg->setText(QCoreApplication::translate("Register", "\345\256\214\346\210\220\346\263\250\345\206\214", nullptr));
        label_log->setText(QString());
        label_name->setText(QCoreApplication::translate("Register", "Matrix", nullptr));
        label_statusUser->setText(QCoreApplication::translate("Register", "TextLabel", nullptr));
        label_statusPwd->setText(QCoreApplication::translate("Register", "TextLabel", nullptr));
        label_statusIdtiPwd->setText(QCoreApplication::translate("Register", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
