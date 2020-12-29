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
    connect(ui->KatalogBtn, SIGNAL(clicked()), this, SLOT(sendUser()));

    connect(ktlg, SIGNAL(returnToMenu()), this, SLOT(backToMenu()));

    ui->stackedWidget->addWidget(ktlg);
    ui->stackedWidget->addWidget(srch);
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
    if(user.role == 2){
        ui->StatsBtn->hide();
        ui->User_ControlBtn->hide();
    }
    ui->usernameLabel->setText("Добро пожаловать, " + QString::fromLocal8Bit(user.login.c_str()));
}

void mainMenu::backToMenu()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_KatalogBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
