#include "Headers/dialog.h"
#include <QApplication>
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog* dlg = new Dialog;
    dlg->show();
    return a.exec();
}
