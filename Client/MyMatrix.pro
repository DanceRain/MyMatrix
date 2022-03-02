#-------------------------------------------------
#
# Project created by QtCreator 2022-01-01T14:19:06
#
#-------------------------------------------------

QT += core gui
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMatrix
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
		Sources/dialog.cpp \
		Sources/main.cpp \
		Sources/register.cpp \
		Sources/talk_to_server.cpp \
		Sources/usermainwindow.cpp \
		Sources/userdetaildlg.cpp \
		Sources/userinfor.cpp \
		Sources/MuItemDelegate.cpp\


HEADERS += \
		Headers/dialog.h \
		Headers/register.h \
		Headers/usermainwindow.h \
		Headers/userdetaildlg.h \
		Headers/userinfor.h \
		Headers/MuItemDelegate.h \
		Headers/MuListItemData.h \
		Headers/talk_to_server.h

FORMS += \
		Forms/dialog.ui \
		Forms/register.ui \
		Forms/usermainwindow.ui \
		Forms/userdetaildlg.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resource/qss.qrc \
	resource/ui.qrc \

LIBS += -lwsock32
