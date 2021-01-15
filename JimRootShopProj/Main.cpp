#include "mainwindow.h"
#include "mainmenu.h"
#include "katalog.h"
#include "Header.h"
#include "addguitars.h"
#include "guitarpage.h"
#include "search.h"
#include <iostream>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Guitar Shop Jim Root's Kadyk");
    QIcon winIcon("Icons\\main.ico");
    w.setWindowIcon(winIcon);
    return a.exec();
}
