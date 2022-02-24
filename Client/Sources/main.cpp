#include "Headers/dialog.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "Headers/talk_to_server.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Talk_To_Server* server = new Talk_To_Server(QStringLiteral("ws://112.126.96.244:9999"));
    Dialog* dlg = new Dialog(server);
    dlg->show();
    return a.exec();
}
