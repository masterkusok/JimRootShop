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
}

MainWindow::~MainWindow()
{
    delete ui;
}

//нажатие на кнопку войти
void MainWindow::on_loginConfirm_clicked()
{
    User Users[100];
    ParseUsers(Users);
    std::cout << Users[1].login << " " << Users[1].password << " " << Users[1].role;
    std::string login = ui->loginLogin->text().toStdString();
    std::string password = ui->loginPassword->text().toStdString();

    if(CheckUsers(Users, password, login) > 0){
         QMessageBox::information(this, "вход", "вы успешно вошли");
    }
    else{
        QMessageBox::information(this, "вход", "че то не то, попробуй еще раз");
        ui->loginLogin->clear();
        ui->loginPassword->clear();
    }
}

//нажатие на кнопку регистрации и непосредственно алгоритм регистрации
void MainWindow::on_regConfirm_clicked()
{
    User Users[100];
    ParseUsers(Users);
    std::string login = ui->regLogin->text().toStdString();
    std::string password = ui->regPassword->text().toStdString();
    if(login != "" && password != "" && login != " " && password != " "){
        if(CheckUsers(Users, password, login) == 0){
            int number = getNumberOfUsers(Users);
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
           QMessageBox::information(this, "регистрация", "вы успешно зарегестрированы");
           ui->regLogin->clear();
           ui->regPassword->clear();
        }
        else{
            QMessageBox::information(this, "регистрация", "такой пользователь уже зареган тварь");
        }
    }
    else{
        QMessageBox::information(this, "регистрация", "ты совсем тупой, может поля заполнишь, не?");
    }
}
