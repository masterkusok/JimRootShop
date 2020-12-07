#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <iostream>
#include "Header.h"
#include <QMessageBox>

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
void mainMenu::recieveData(User user){
    if(user.role == 2){
        ui->StatsBtn->hide();
        ui->User_ControlBtn->hide();
    }
}

void mainMenu::on_KatalogBtn_clicked()
{
    Katalog *katalog = new Katalog();
    this->hide();
    katalog->show();
}
