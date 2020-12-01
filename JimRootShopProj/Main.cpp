#include "mainwindow.h"
#include "mainmenu.h"
#include "Header.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
