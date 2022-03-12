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
		Sources/bubble_frame.cpp \
		Sources/chat_item_base.cpp \
		Sources/chat_view.cpp \
		Sources/login.cpp \
		Sources/main.cpp \
		Sources/message_text_edit.cpp \
		Sources/mult_item_delegate.cpp \
		Sources/picture_bubble.cpp \
		Sources/register.cpp \
		Sources/talk_to_server.cpp \
		Sources/text_bubble.cpp \
		Sources/user_detail_dlg.cpp \
		Sources/user_main_window.cpp \
		Sources/userinfor.cpp


HEADERS += \
		Headers/bubble_frame.h \
		Headers/chat_item_base.h \
		Headers/chat_role.h \
		Headers/chat_view.h \
		Headers/login.h \
		Headers/message_text_edit.h \
		Headers/mult_item_data.h \
		Headers/mult_item_delegate.h \
		Headers/picture_bubble.h \
		Headers/register.h \
		Headers/text_bubble.h \
		Headers/user_detail_dlg.h \
		Headers/user_main_window.h \
		Headers/userinfor.h \
		Headers/talk_to_server.h \
		Headers/httplib.h

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
LIBS += -lws2_32

