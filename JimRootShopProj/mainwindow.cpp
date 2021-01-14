#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Header.h"
#include <iostream>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);

    MainMenu = new mainMenu();
    ktlg = new Katalog();
    srch = new Search();
    gtp = new GuitarPage();
    cntrl = new UserControl();
    addgi = new addguitars();

    connect(ui->loginConfirm,SIGNAL(clicked()),this,SLOT(onLoginSend()));
    connect(this,SIGNAL(sendData(User)), MainMenu,SLOT(recieveData(User)));

    connect(ktlg, SIGNAL(backToMainMenu()), this, SLOT(showMenu()));

    connect(srch, SIGNAL(returnToMenu()), this, SLOT(showMenu()));

    connect(MainMenu, SIGNAL(goToKatalog()), this, SLOT(showKatalog()));
    connect(MainMenu, SIGNAL(goToSearch()), this, SLOT(showSearch()));
    connect(MainMenu,SIGNAL(goBack()), this, SLOT(showMainWindow()));
    connect(MainMenu, SIGNAL(goToUserControl()), this, SLOT(showUserControl()));
    connect(MainMenu, SIGNAL(goToAddGuitar()), this, SLOT(showAddGuitar()));

    connect(addgi,SIGNAL(goBack()),this,SLOT(showMenu()));

    ui->stackedWidget->addWidget(MainMenu);
    ui->stackedWidget->addWidget(ktlg);
    ui->stackedWidget->addWidget(srch);
    ui->stackedWidget->addWidget(cntrl);
    ui->stackedWidget->addWidget(addgi);

}
User UserThatLogined;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMenu()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showKatalog()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::onLoginSend(){
    emit sendData(UserThatLogined);
}
//нажатие на кнопку войти
void MainWindow::on_loginConfirm_clicked()
{
    User Users[getNumberOfUsers()];
    ParseUsers(Users);
    std::string login = ui->loginLogin->text().toStdString();
    std::string password = ui->loginPassword->text().toStdString();

    if(CheckUsers(Users, password, login) >= 0){
        UserThatLogined = getUserInformationByLoginAndPassword(login,password);
        ui->stackedWidget->setCurrentIndex(2);
    }
    else{
        if(login != "" && password != "" && login != " " && password != " "){
            QMessageBox::information(this, "Authorize", "Password or login are incorrect, try other");
            ui->loginLogin->clear();
            ui->loginPassword->clear();
        }
    }
}

//нажатие на кнопку регистрации и непосредственно алгоритм регистрации
void MainWindow::on_regConfirm_clicked()
{
    User Users[getNumberOfUsers() + 1];
    ParseUsers(Users);
    std::string login = ui->regLogin->text().toStdString();
    std::string password = ui->regPassword->text().toStdString();
    if(login != "" && password != "" && login != " " && password != " "){
        if(CheckUsers(Users, password, login) == 0){
            int number = getNumberOfUsers();
            Users[number].login = login;
            Users[number].password = password;
            Users[number].id = number;
            if(ui->ifMaster->isChecked()){
                Users[number].role = 3;
                QMessageBox::information(this, "Registration", "Your request was succesfully placed, now wait until other admin accept or decline it");

            }
            else{
                Users[number].role = 2;
                QMessageBox::information(this, "Registration", "Registration completed succesfully");
            }
           std::fstream WriteFile;
           WriteFile.open("Files\\Users.csv", std::ios::app);
           WriteFile << login << " " << password << " " << Users[number].role << std::endl;
           WriteFile.close();
           ui->regLogin->clear();
           ui->regPassword->clear();

        }
        else{
            QMessageBox::information(this, "Registration", "User with same login already exists");
        }
    }
}

void MainWindow::showSearch()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::showMainWindow(){
    ui->loginLogin->clear();
    ui->loginPassword->clear();
    ui->regLogin->clear();
    ui->regPassword->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showUserControl()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::showAddGuitar(){
    ui->stackedWidget->setCurrentIndex(6);
}
