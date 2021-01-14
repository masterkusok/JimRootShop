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
    scrollCont->setStyleSheet("QWidget{font-family: Segoe ui black; font-size:8pt}");
    QGridLayout *scrollingLayout = new QGridLayout();

    int number = getNumberOfUsers();
    std::vector <User> Users = ParseUsers();

    QLabel *LoginLbl = new QLabel();
    LoginLbl->setText("Login");
    LoginLbl->setStyleSheet("QLabel{font-size:11pt}");
    scrollingLayout->addWidget(LoginLbl, 0, 1);

    QLabel *RoleLbl = new QLabel();
    RoleLbl->setText("Post");
    RoleLbl->setStyleSheet("QLabel{font-size:11pt}");
    scrollingLayout->addWidget(RoleLbl, 0, 2);

    QLabel *ActionLbl = new QLabel();
    ActionLbl->setText("Allowed Actions");
    ActionLbl->setStyleSheet("QLabel{font-size:11pt}");
    scrollingLayout->addWidget(ActionLbl, 0, 4);

    for(int i = 0; i < number; i++){
        if(!Users[i].login.empty() && !Users[i].password.empty() && Users[i].role!=0){
            std::cout << Users[i].login << Users[i].password << Users[i].role << std::endl;
            //отображение логина
            QLabel *login = new QLabel();
            QString qLogin = QString::fromUtf8(Users[i].login.c_str());
            login->setText(qLogin);

            //отображение роли
            QLabel *role = new QLabel();
            QString qrole;
            if(Users[i].role == 3 or Users[i].role == 1){
                qrole = "Admin";
            }
            else if(Users[i].role == 2){
                qrole = "User";
            }
            else{
                qrole = "Banned";
            }
            role->setText(qrole);

            scrollingLayout->addWidget(login, i+1, 1);
            scrollingLayout->addWidget(role, i+1, 2);


            if(Users[i].role == 3){
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

                scrollingLayout->addWidget(AcceptBtn, i+1, 3);
                scrollingLayout->addWidget(CancelBtn, i+1, 4);
            }
            if(Users[i].role == 2){
                QString buttonNum = QString::number(i);

                //кнопка для повышения должности юзера
                QPushButton *promoteBtn = new QPushButton(this);
                promoteBtn->setText("Promote User");
                promoteBtn->setObjectName("PromoteBtn" + buttonNum);

                //кнопка бана
                QPushButton *banBtn = new QPushButton(this);
                banBtn->setText("Ban User");
                banBtn->setObjectName("BanBtn" + buttonNum);
                banBtn->setStyleSheet("QPushButton{background-color:#e8463a;} QPushButton:hover{background-color:#cc3e33;}");

                scrollingLayout->addWidget(promoteBtn, i+1, 3);
                scrollingLayout->addWidget(banBtn, i+1, 4);
            }
            if(Users[i].role == 4){
                //кнопка для разбана
                QString buttonNum = QString::number(i);
                QPushButton *unbanBtn = new QPushButton(this);
                unbanBtn->setText("Unban User");
                unbanBtn->setObjectName("UnbanBtn" + buttonNum);
                scrollingLayout->addWidget(unbanBtn, i+1, 3);
            }
        }
    }

    scrollingLayout->setHorizontalSpacing(50);
    scrollingLayout->setVerticalSpacing(70);

    for(int i = 0; i < number; i++){
        QString buttonNum = QString::number(i);

        QPushButton *AcceptBtn = findChild<QPushButton*>("AcceptBtn" + buttonNum);
        if(AcceptBtn!=nullptr){
            AcceptBtn->setProperty("index", i);
            connect(AcceptBtn, SIGNAL(clicked()), this, SLOT(AcceptClicked()));
        }

        QPushButton *CancelBtn = findChild<QPushButton*>("CancelBtn" + buttonNum);
        if(CancelBtn!=nullptr){
            CancelBtn->setProperty("index", i);
            connect(CancelBtn, SIGNAL(clicked()), this, SLOT(CancelClicked()));
        }

        QPushButton *banBtn = findChild<QPushButton*>("BanBtn" + buttonNum);
        if(banBtn!=nullptr){
            banBtn->setProperty("index", i);
            connect(banBtn, SIGNAL(clicked()), this, SLOT(banClicked()));
        }

        QPushButton *unbanBtn = findChild<QPushButton*>("UnbanBtn" + buttonNum);
        if(unbanBtn!=nullptr){
            unbanBtn->setProperty("index", i);
            connect(unbanBtn, SIGNAL(clicked()), this, SLOT(unbanClicked()));
        }

        QPushButton *promBtn = findChild<QPushButton*>("PromoteBtn" + buttonNum);
        if(promBtn!=nullptr){
            promBtn->setProperty("index", i);
            connect(promBtn, SIGNAL(clicked()), this, SLOT(promClicked()));
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
    changeUserRole(user_index, 1);
    update();
}

void UserControl::banClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int user_index = button->property("index").toInt();
    changeUserRole(user_index, 4);
    update();
}

void UserControl::unbanClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int user_index = button->property("index").toInt();
    changeUserRole(user_index, 2);
    update();
}

void UserControl::promClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int user_index = button->property("index").toInt();
    changeUserRole(user_index, 1);
    update();
}
