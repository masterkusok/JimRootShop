#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <iostream>
#include "Header.h"
#include <QMessageBox>
#include <QLabel>
mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    ktlg = new Katalog();
    srch = new Search();

    connect(this, SIGNAL(sendData(User)), ktlg, SLOT(recieveData(User)));
    connect(this, SIGNAL(sendData(User)), srch, SLOT(recieveData(User)));

    connect(ui->KatalogBtn, SIGNAL(clicked()), this, SLOT(sendUser()));


}

mainMenu::~mainMenu()
{
    delete ui;
}
void mainMenu::sendUser(){
    emit sendData(current_user);
}
void mainMenu::recieveData(User user){
    current_user = user;
    if(user.role == 2 || user.role == 0){
        ui->AddGuitarBtn->hide();
        ui->User_ControlBtn->hide();
    }
    else{
        ui->AddGuitarBtn->show();
        ui->User_ControlBtn->show();
    }
    ui->usernameLabel->setText("Welcome, " + QString::fromLocal8Bit(user.login.c_str()));
}


void mainMenu::on_KatalogBtn_clicked()
{
    emit goToKatalog();
}

void mainMenu::on_SearchBtn_clicked()
{
    emit sendData(current_user);
    emit goToSearch();
}

void mainMenu::on_ExitBtn_clicked()
{
    emit goBack();
}

void mainMenu::on_User_ControlBtn_clicked()
{
    emit goToUserControl();
}

void mainMenu::on_AddGuitarBtn_clicked()
{
    emit goToAddGuitar();
}
