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

    connect(ui->loginConfirm,SIGNAL(clicked()),this,SLOT(onLoginSend()));
    connect(this,SIGNAL(sendData(User)), MainMenu,SLOT(recieveData(User)));

    connect(ktlg, SIGNAL(backToMainMenu()), this, SLOT(showMenu()));
    connect(srch, SIGNAL(returnToMenu()), this, SLOT(showMenu()));

    connect(MainMenu, SIGNAL(goToKatalog()), this, SLOT(showKatalog()));
    connect(MainMenu, SIGNAL(goToSearch()), this, SLOT(showSearch()));

    ui->stackedWidget->addWidget(MainMenu);
    ui->stackedWidget->addWidget(ktlg);
    ui->stackedWidget->addWidget(srch);


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

    if(CheckUsers(Users, password, login) > 0){
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
                Users[number].role = 1;

            }
            else{
                Users[number].role = 2;
            }
           std::fstream WriteFile;
           WriteFile.open("Files\\Users.csv", std::ios::app);
           WriteFile << login << " " << password << " " << Users[number].role << std::endl;
           WriteFile.close();
           ui->regLogin->clear();
           ui->regPassword->clear();
           QMessageBox::information(this, "Registration", "Registration completed succesfully");
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
