#include "katalog.h"
#include "ui_katalog.h"
#include <QApplication>
#include <QPushButton>
#include <QLayout>
#include <QScrollArea>
#include <QLabel>

Katalog::Katalog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Katalog)
{

    btnNumber = NULL;
    ui->setupUi(this);

    //mmn = new mainMenu();
    gtp = new GuitarPage();

    Instrument Guitars[30];
    ParseGuitars(Guitars);
    int number = getNumberOfGuitars(Guitars);
    //подключение сигнала для отправления на форму guitarpage
    connect(this, SIGNAL(sendData(User, int)), gtp, SLOT(recieveData(User, int)));

    //подключение сигналов для отправления обратно в меню
   // connect(this, SIGNAL(returnUser(User)), mmn, SLOT(recieveData(User)));
   // connect(ui->returnToMenuButton, SIGNAL(clicked()), mmn,  SLOT(show()));
    //connect(ui->returnToMenuButton, SIGNAL(clicked()), this, SLOT(on_returnToMenuButton_clicked()));

    //это всякая хрень что бы работал скролл
    QScrollArea *scrolling = new QScrollArea(this);
    scrolling->widgetResizable();
    scrolling->resize(500, 350);
    QWidget *scrollCont = new QWidget();
    QGridLayout *scrollingLayout = new QGridLayout();

    for(int i = 0; i < number; i++){
        if(Guitars[i].name != " "){
            //Добавляю изображение, переменная path это путь только в qsring, дальше операции с пиксмапами что бы задать изображение
             QLabel *image = new QLabel();
             QString path = QString::fromUtf8(Guitars[i].img_path.c_str());
             QPixmap startImg("Images\\" + path);
             QPixmap finalImg =  startImg.scaled(100, 100);
             image->setPixmap(finalImg);

             //задаем имя
             QLabel *name = new QLabel();
             QString qName = QString::fromUtf8(Guitars[i].name.c_str());
             name->setText(qName);

             //задаем стоимость
             QLabel *price = new QLabel();
             QString qPrice = QString::number(Guitars[i].price);
             price->setText(qPrice + "$");

             //создаем кноп очку
             QPushButton *btn = new QPushButton(this);
             btn->setText("перейти");

             scrollingLayout->setHorizontalSpacing(50);
             scrollingLayout->setVerticalSpacing(70);

             QString buttonNum = QString::number(i);
             btn->setObjectName("button" + buttonNum);
             scrollingLayout->addWidget(image, i, 1);
             scrollingLayout->addWidget(name, i, 2);
             scrollingLayout->addWidget(price, i, 3);
             scrollingLayout->addWidget(btn, i, 4);
        }
    }

    //тут я приязываю к каждой кнопке клик
    for(int i = 0; i < number; i++){
        QString buttonNum = QString::number(i);
        QPushButton *button = findChild<QPushButton*>("button" + buttonNum);
        if(button!=nullptr){
            //это нужно что бы в слоте получать номер гитары на которую нажали
            button->setProperty("index", i);
            connect(button, SIGNAL(clicked()), gtp,  SLOT(show()));
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

    scrollCont->setLayout(scrollingLayout);
    scrolling->setWidget(scrollCont);
    scrolling->setGeometry(110, 140, 751, 381);
    scrolling->show();

}

void Katalog::buttonClicked(){
    //получаем эту самую циферку, и открываем окно
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    // вот в этой переменной ты можешь найти интовую циферку, которую вместе с юзером нужно в гитарпейдж перекинуть
    guitar_index = button->property("index").toInt();
    User user;
    emit sendData(user, guitar_index);
    this->close();
}

Katalog::~Katalog()
{
    delete ui;
}
void Katalog:: recieveData(User user){
    std::cout << user.login;
}

void Katalog::on_returnToMenuButton_clicked()
{

    this->close();
}
