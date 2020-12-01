#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "Header.h"

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
}

mainMenu::~mainMenu()
{
    delete ui;
}
