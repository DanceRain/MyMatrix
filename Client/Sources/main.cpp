#include "Headers/login.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "Headers/talk_to_server.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog* dlg = new Dialog();
    dlg->show();
    return a.exec();
}
