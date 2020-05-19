#include "acr_testqt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ACR_TestQt w;
    w.show();
    return a.exec();
}
