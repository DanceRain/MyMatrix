#include "Headers/login.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "Headers/talk_to_server.h"
#include "Headers/httplib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Talk_To_Server cli;
    Dialog* dlg = new Dialog(nullptr, &cli);
    dlg->show();
    return a.exec();
}
