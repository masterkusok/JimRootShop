#include "mainwindow.h"
#include "mainmenu.h"
#include "katalog.h"
#include "Header.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Katalog ktlg;
    ktlg.show();
    return a.exec();
}
