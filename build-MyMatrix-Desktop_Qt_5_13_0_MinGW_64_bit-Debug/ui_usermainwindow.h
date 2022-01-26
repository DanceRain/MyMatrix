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
    QHBoxLayout *hla_ceterWidget;
    QWidget *widget_nav;
    QVBoxLayout *vla_nav;
    QPushButton *ptn_userIcon;
    QVBoxLayout *vla_unity;
    QPushButton *ptn_message;
    QPushButton *ptn_friendList;
    QPushButton *ptn_file;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *vla_unityInfor;
    QHBoxLayout *hla_find;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_addFriend;
    QListWidget *listWidget_unityList;
    QWidget *layoutWidget1;
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
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        hla_ceterWidget = new QHBoxLayout();
        hla_ceterWidget->setSpacing(7);
        hla_ceterWidget->setObjectName(QString::fromUtf8("hla_ceterWidget"));
        widget_nav = new QWidget(centralwidget);
        widget_nav->setObjectName(QString::fromUtf8("widget_nav"));
        widget_nav->setMinimumSize(QSize(100, 600));
        vla_nav = new QVBoxLayout(widget_nav);
        vla_nav->setSpacing(10);
        vla_nav->setObjectName(QString::fromUtf8("vla_nav"));
        vla_nav->setSizeConstraint(QLayout::SetMinAndMaxSize);
        vla_nav->setContentsMargins(0, 0, 0, 0);
        ptn_userIcon = new QPushButton(widget_nav);
        ptn_userIcon->setObjectName(QString::fromUtf8("ptn_userIcon"));
        ptn_userIcon->setMinimumSize(QSize(80, 60));
        ptn_userIcon->setMaximumSize(QSize(80, 16777215));

        vla_nav->addWidget(ptn_userIcon);

        vla_unity = new QVBoxLayout();
        vla_unity->setObjectName(QString::fromUtf8("vla_unity"));
        ptn_message = new QPushButton(widget_nav);
        ptn_message->setObjectName(QString::fromUtf8("ptn_message"));
        ptn_message->setMinimumSize(QSize(80, 35));
        ptn_message->setMaximumSize(QSize(80, 35));

        vla_unity->addWidget(ptn_message);

        ptn_friendList = new QPushButton(widget_nav);
        ptn_friendList->setObjectName(QString::fromUtf8("ptn_friendList"));
        ptn_friendList->setMinimumSize(QSize(0, 35));
        ptn_friendList->setMaximumSize(QSize(80, 16777215));

        vla_unity->addWidget(ptn_friendList);

        ptn_file = new QPushButton(widget_nav);
        ptn_file->setObjectName(QString::fromUtf8("ptn_file"));
        ptn_file->setMinimumSize(QSize(0, 35));
        ptn_file->setMaximumSize(QSize(80, 16777215));

        vla_unity->addWidget(ptn_file);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vla_unity->addItem(verticalSpacer);


        vla_nav->addLayout(vla_unity);


        hla_ceterWidget->addWidget(widget_nav);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setLayoutDirection(Qt::LeftToRight);
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(0);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        vla_unityInfor = new QVBoxLayout(layoutWidget);
        vla_unityInfor->setSpacing(0);
        vla_unityInfor->setObjectName(QString::fromUtf8("vla_unityInfor"));
        vla_unityInfor->setSizeConstraint(QLayout::SetMaximumSize);
        vla_unityInfor->setContentsMargins(0, 0, 0, 0);
        hla_find = new QHBoxLayout();
        hla_find->setSpacing(0);
        hla_find->setObjectName(QString::fromUtf8("hla_find"));
        hla_find->setSizeConstraint(QLayout::SetMaximumSize);
        hla_find->setContentsMargins(-1, 6, -1, 5);
        lineEdit_search = new QLineEdit(layoutWidget);
        lineEdit_search->setObjectName(QString::fromUtf8("lineEdit_search"));
        lineEdit_search->setMinimumSize(QSize(150, 0));
        lineEdit_search->setMaximumSize(QSize(200, 16777215));

        hla_find->addWidget(lineEdit_search);

        pushButton_addFriend = new QPushButton(layoutWidget);
        pushButton_addFriend->setObjectName(QString::fromUtf8("pushButton_addFriend"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_addFriend->sizePolicy().hasHeightForWidth());
        pushButton_addFriend->setSizePolicy(sizePolicy);
        pushButton_addFriend->setMinimumSize(QSize(50, 0));
        pushButton_addFriend->setMaximumSize(QSize(50, 16777215));

        hla_find->addWidget(pushButton_addFriend);


        vla_unityInfor->addLayout(hla_find);

        listWidget_unityList = new QListWidget(layoutWidget);
        listWidget_unityList->setObjectName(QString::fromUtf8("listWidget_unityList"));
        listWidget_unityList->setMinimumSize(QSize(300, 0));
        listWidget_unityList->setMaximumSize(QSize(300, 16777215));

        vla_unityInfor->addWidget(listWidget_unityList);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        vla_unityList = new QVBoxLayout(layoutWidget1);
        vla_unityList->setSpacing(0);
        vla_unityList->setObjectName(QString::fromUtf8("vla_unityList"));
        vla_unityList->setContentsMargins(0, 0, 0, 0);
        hla_quitAndMin = new QHBoxLayout();
        hla_quitAndMin->setSpacing(0);
        hla_quitAndMin->setObjectName(QString::fromUtf8("hla_quitAndMin"));
        hla_quitAndMin->setContentsMargins(10, -1, 20, 5);
        label_name = new QLabel(layoutWidget1);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        hla_quitAndMin->addWidget(label_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hla_quitAndMin->addItem(horizontalSpacer);

        pushButton_maxmize = new QPushButton(layoutWidget1);
        pushButton_maxmize->setObjectName(QString::fromUtf8("pushButton_maxmize"));
        pushButton_maxmize->setMinimumSize(QSize(30, 30));
        pushButton_maxmize->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_maxmize);

        pushButton_minimize = new QPushButton(layoutWidget1);
        pushButton_minimize->setObjectName(QString::fromUtf8("pushButton_minimize"));
        pushButton_minimize->setMinimumSize(QSize(30, 30));
        pushButton_minimize->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_minimize);

        pushButton_shutdown = new QPushButton(layoutWidget1);
        pushButton_shutdown->setObjectName(QString::fromUtf8("pushButton_shutdown"));
        pushButton_shutdown->setEnabled(true);
        pushButton_shutdown->setMinimumSize(QSize(30, 30));
        pushButton_shutdown->setIconSize(QSize(30, 30));

        hla_quitAndMin->addWidget(pushButton_shutdown);


        vla_unityList->addLayout(hla_quitAndMin);

        plainTextEdit = new QPlainTextEdit(layoutWidget1);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(true);

        vla_unityList->addWidget(plainTextEdit);

        splitter->addWidget(layoutWidget1);

        hla_ceterWidget->addWidget(splitter);


        verticalLayout_4->addLayout(hla_ceterWidget);

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
