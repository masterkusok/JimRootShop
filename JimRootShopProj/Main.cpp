#include "mainwindow.h"
#include "mainmenu.h"
#include "katalog.h"
#include "Header.h"
#include "guitarpage.h"
#include <iostream>
#include <QTextCodec>
int main(int argc, char *argv[])
{

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Katalog ktlg;
    ktlg.show();
    //GuitarPage gtp;
    //gtp.show();
    return a.exec();
}
