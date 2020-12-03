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
    connect(ui->loginConfirm,SIGNAL(clicked()),this,SLOT(onLoginSend()));
    connect(this,SIGNAL(sendData(User)), MainMenu,SLOT(recieveData(User)));
}
User UserThatLogined;
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onLoginSend(){
    emit sendData(UserThatLogined);
}
//нажатие на кнопку войти
void MainWindow::on_loginConfirm_clicked()
{
    User Users[getNumberOfUsers()];
    ParseUsers(Users);
//    std::cout << Users[1].login << " " << Users[1].password << " " << Users[1].role;
    std::string login = ui->loginLogin->text().toStdString();
    std::string password = ui->loginPassword->text().toStdString();

    if(CheckUsers(Users, password, login) > 0){
        UserThatLogined = getUserInformationByLoginAndPassword(login,password);
        this->hide();
        MainMenu->show();
    }
    else{
        if(login != "" && password != "" && login != " " && password != " "){
            QMessageBox::information(this, "вход", "Вы ввели неправильный логин или пароль попробуйте ещё");
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
                this->hide();

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
           QMessageBox::information(this, "регистрация", "Вы успешно зарегестрированы");
        }
        else{
            QMessageBox::information(this, "регистрация", "Пользователь с таким логином уже зарегестрирован");
        }
    }
}
