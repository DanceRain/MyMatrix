/********************************************************************************
** Form generated from reading UI file 'usermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMAINWINDOW_H
#define UI_USERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMainWindow
{
public:
    QAction *actionMessage;
    QAction *actionFriend;
    QAction *actionFile;
    QAction *actionUserInfo;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vla_unityButton;
    QPushButton *ptn_userIcon;
    QVBoxLayout *vla_unity;
    QPushButton *ptn_message;
    QPushButton *ptn_friendList;
    QPushButton *ptn_file;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *vla_unityInfor;
    QHBoxLayout *hla_find;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_addFriend;
    QListWidget *listWidget_unityList;
    QWidget *widget1;
    QVBoxLayout *vla_unityList;
    QHBoxLayout *hla_quitAndMin;
    QLabel *label_name;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_maxmize;
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_shutdown;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QMainWindow *UserMainWindow)
    {
        if (UserMainWindow->objectName().isEmpty())
            UserMainWindow->setObjectName(QString::fromUtf8("UserMainWindow"));
        UserMainWindow->resize(800, 600);
        UserMainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionMessage = new QAction(UserMainWindow);
        actionMessage->setObjectName(QString::fromUtf8("actionMessage"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../resource/image/icon/message.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMessage->setIcon(icon);
        actionFriend = new QAction(UserMainWindow);
        actionFriend->setObjectName(QString::fromUtf8("actionFriend"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ui/image/icon/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFriend->setIcon(icon1);
        actionFile = new QAction(UserMainWindow);
        actionFile->setObjectName(QString::fromUtf8("actionFile"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ui/image/icon/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFile->setIcon(icon2);
        actionUserInfo = new QAction(UserMainWindow);
        actionUserInfo->setObjectName(QString::fromUtf8("actionUserInfo"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ui/image/icon/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUserInfo->setIcon(icon3);
        centralwidget = new QWidget(UserMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        vla_unityButton = new QVBoxLayout();
        vla_unityButton->setSpacing(15);
        vla_unityButton->setObjectName(QString::fromUtf8("vla_unityButton"));
        vla_unityButton->setSizeConstraint(QLayout::SetMaximumSize);
        vla_unityButton->setContentsMargins(-1, 0, -1, -1);
        ptn_userIcon = new QPushButton(centralwidget);
        ptn_userIcon->setObjectName(QString::fromUtf8("ptn_userIcon"));
        ptn_userIcon->setMinimumSize(QSize(80, 60));
        ptn_userIcon->setMaximumSize(QSize(16777215, 16777215));

        vla_unityButton->addWidget(ptn_userIcon);

        vla_unity = new QVBoxLayout();
        vla_unity->setObjectName(QString::fromUtf8("vla_unity"));
        ptn_message = new QPushButton(centralwidget);
        ptn_message->setObjectName(QString::fromUtf8("ptn_message"));
        ptn_message->setMinimumSize(QSize(0, 35));

        vla_unity->addWidget(ptn_message);

        ptn_friendList = new QPushButton(centralwidget);
        ptn_friendList->setObjectName(QString::fromUtf8("ptn_friendList"));
        ptn_friendList->setMinimumSize(QSize(0, 35));

        vla_unity->addWidget(ptn_friendList);

        ptn_file = new QPushButton(centralwidget);
        ptn_file->setObjectName(QString::fromUtf8("ptn_file"));
        ptn_file->setMinimumSize(QSize(0, 35));

        vla_unity->addWidget(ptn_file);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vla_unity->addItem(verticalSpacer);


        vla_unityButton->addLayout(vla_unity);


        horizontalLayout->addLayout(vla_unityButton);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setLayoutDirection(Qt::LeftToRight);
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(0);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        vla_unityInfor = new QVBoxLayout(widget);
        vla_unityInfor->setSpacing(0);
        vla_unityInfor->setObjectName(QString::fromUtf8("vla_unityInfor"));
        vla_unityInfor->setSizeConstraint(QLayout::SetMaximumSize);
        vla_unityInfor->setContentsMargins(0, 0, 0, 0);
        hla_find = new QHBoxLayout();
        hla_find->setSpacing(0);
        hla_find->setObjectName(QString::fromUtf8("hla_find"));
        hla_find->setSizeConstraint(QLayout::SetMaximumSize);
        hla_find->setContentsMargins(-1, 6, -1, 5);
        lineEdit_search = new QLineEdit(widget);
        lineEdit_search->setObjectName(QString::fromUtf8("lineEdit_search"));
        lineEdit_search->setMinimumSize(QSize(150, 0));
        lineEdit_search->setMaximumSize(QSize(200, 16777215));

        hla_find->addWidget(lineEdit_search);

        pushButton_addFriend = new QPushButton(widget);
        pushButton_addFriend->setObjectName(QString::fromUtf8("pushButton_addFriend"));
        pushButton_addFriend->setMinimumSize(QSize(50, 0));
        pushButton_addFriend->setMaximumSize(QSize(50, 16777215));

        hla_find->addWidget(pushButton_addFriend);


        vla_unityInfor->addLayout(hla_find);

        listWidget_unityList = new QListWidget(widget);
        listWidget_unityList->setObjectName(QString::fromUtf8("listWidget_unityList"));
        listWidget_unityList->setMinimumSize(QSize(300, 0));
        listWidget_unityList->setMaximumSize(QSize(300, 16777215));

        vla_unityInfor->addWidget(listWidget_unityList);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        vla_unityList = new QVBoxLayout(widget1);
        vla_unityList->setSpacing(0);
        vla_unityList->setObjectName(QString::fromUtf8("vla_unityList"));
        vla_unityList->setContentsMargins(0, 0, 0, 0);
        hla_quitAndMin = new QHBoxLayout();
        hla_quitAndMin->setSpacing(0);
        hla_quitAndMin->setObjectName(QString::fromUtf8("hla_quitAndMin"));
        hla_quitAndMin->setContentsMargins(10, -1, 20, 5);
        label_name = new QLabel(widget1);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        hla_quitAndMin->addWidget(label_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hla_quitAndMin->addItem(horizontalSpacer);

        pushButton_maxmize = new QPushButton(widget1);
        pushButton_maxmize->setObjectName(QString::fromUtf8("pushButton_maxmize"));
        pushButton_maxmize->setMinimumSize(QSize(30, 30));
        pushButton_maxmize->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_maxmize);

        pushButton_minimize = new QPushButton(widget1);
        pushButton_minimize->setObjectName(QString::fromUtf8("pushButton_minimize"));
        pushButton_minimize->setMinimumSize(QSize(30, 30));
        pushButton_minimize->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_minimize);

        pushButton_shutdown = new QPushButton(widget1);
        pushButton_shutdown->setObjectName(QString::fromUtf8("pushButton_shutdown"));
        pushButton_shutdown->setEnabled(true);
        pushButton_shutdown->setMinimumSize(QSize(30, 30));
        pushButton_shutdown->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_shutdown);


        vla_unityList->addLayout(hla_quitAndMin);

        plainTextEdit = new QPlainTextEdit(widget1);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(true);

        vla_unityList->addWidget(plainTextEdit);

        splitter->addWidget(widget1);

        horizontalLayout->addWidget(splitter);


        verticalLayout_4->addLayout(horizontalLayout);

        UserMainWindow->setCentralWidget(centralwidget);

        retranslateUi(UserMainWindow);
        QObject::connect(pushButton_minimize, SIGNAL(clicked()), UserMainWindow, SLOT(showMinimized()));
        QObject::connect(pushButton_shutdown, SIGNAL(clicked()), UserMainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(UserMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserMainWindow)
    {
        UserMainWindow->setWindowTitle(QCoreApplication::translate("UserMainWindow", "MainWindow", nullptr));
        actionMessage->setText(QCoreApplication::translate("UserMainWindow", "Message", nullptr));
#if QT_CONFIG(tooltip)
        actionMessage->setToolTip(QCoreApplication::translate("UserMainWindow", "Recent Message", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMessage->setShortcut(QCoreApplication::translate("UserMainWindow", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFriend->setText(QCoreApplication::translate("UserMainWindow", "Friend", nullptr));
        actionFile->setText(QCoreApplication::translate("UserMainWindow", "File", nullptr));
        actionUserInfo->setText(QCoreApplication::translate("UserMainWindow", "UserInfo", nullptr));
        ptn_userIcon->setText(QString());
        ptn_message->setText(QString());
        ptn_friendList->setText(QString());
        ptn_file->setText(QString());
        pushButton_addFriend->setText(QCoreApplication::translate("UserMainWindow", "searc", nullptr));
        label_name->setText(QCoreApplication::translate("UserMainWindow", "TextLabel", nullptr));
        pushButton_maxmize->setText(QString());
        pushButton_minimize->setText(QString());
        pushButton_shutdown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserMainWindow: public Ui_UserMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMAINWINDOW_H
