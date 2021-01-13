#include "usercontrol.h"
#include "ui_usercontrol.h"

UserControl::UserControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserControl)
{
    ui->setupUi(this);
    update();
}

UserControl::~UserControl()
{
    delete ui;
}

void UserControl::update()
{
    QScrollArea *scrolling = ui->userControlArea;
    QWidget *scrollCont = new QWidget();
    QGridLayout *scrollingLayout = new QGridLayout();

    int number = getNumberOfUsers();
    User users[number];
    ParseUsers(users);

    for(int i = 0; i < number; i++){
        if(!users[i].login.empty() && !users[i].password.empty() && users[i].role!=0){

            std::cout << users[i].login << users[i].password << users[i].role << std::endl;
            //отображение логина
            QLabel *login = new QLabel();
            QString qLogin = QString::fromUtf8(users[i].login.c_str());
            login->setText(qLogin);

            //отображение роли
            QLabel *role = new QLabel();
            QString qrole;
            if(users[i].role == 3 or users[i].role == 1){
                qrole = "Admin";
            }
            else if(users[i].role == 2){
                qrole = "User";
            }
            else{
                qrole = "Banned";
            }
            role->setText(qrole);

            scrollingLayout->addWidget(login, i, 1);
            scrollingLayout->addWidget(role, i, 2);


            if(users[i].role == 3){
                QString buttonNum = QString::number(i);
                //кнопка принятия заявки
                QPushButton *AcceptBtn = new QPushButton(this);
                AcceptBtn->setText("Accept");
                AcceptBtn->setObjectName("AcceptBtn" + buttonNum);
                //кнопка отмены заявки
                QPushButton *CancelBtn = new QPushButton(this);
                CancelBtn->setText("Cancel");
                CancelBtn->setObjectName("CancelBtn" + buttonNum);
                CancelBtn->setStyleSheet("QPushButton{background-color:#e8463a;} QPushButton:hover{background-color:#cc3e33;}");

                scrollingLayout->addWidget(AcceptBtn, i, 3);
                scrollingLayout->addWidget(CancelBtn, i, 4);
            }
        }
    }

    scrollingLayout->setHorizontalSpacing(50);
    scrollingLayout->setVerticalSpacing(70);

    for(int i = 0; i < number; i++){
        QString buttonNum = QString::number(i);
        QPushButton *AcceptBtn = findChild<QPushButton*>("AcceptBtn" + buttonNum);
        if(AcceptBtn!=nullptr){
            //это нужно что бы в слоте получать номер гитары на которую нажали
            AcceptBtn->setProperty("index", i);
            connect(AcceptBtn, SIGNAL(clicked()), this, SLOT(AcceptClicked()));
        }

        QPushButton *CancelBtn = findChild<QPushButton*>("CancelBtn" + buttonNum);
        if(CancelBtn!=nullptr){
            //это нужно что бы в слоте получать номер гитары на которую нажали
            CancelBtn->setProperty("index", i);
            connect(CancelBtn, SIGNAL(clicked()), this, SLOT(CancelClicked()));
        }
    }

    scrollCont->setLayout(scrollingLayout);
    scrolling->setWidget(scrollCont);
}

void UserControl::CancelClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int user_index = button->property("index").toInt();
    DeleteUser(user_index);
    update();
}

void UserControl::AcceptClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int user_index = button->property("index").toInt();
}
