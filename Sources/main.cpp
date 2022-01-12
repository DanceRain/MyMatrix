#include "Headers/dialog.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    w.show();

    return a.exec();
}
