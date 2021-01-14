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
    ui->setupUi(this);
    update();

}

User userToSend;

void Katalog::update()
{
    btnNumber = NULL;
    gtp = new GuitarPage();

    std::vector<Instrument> Guitars = ParseGuitars();

    //подключение сигнала для отправления на форму guitarpage
    connect(this, SIGNAL(sendData(Instrument, User)), gtp, SLOT(recieveData(Instrument, User)));

    ui->stackedWidget->addWidget(gtp);
    connect(gtp, SIGNAL(returnToKatalog()), this, SLOT(backToKatalog()));

    //это всякая хрень что бы работал скролл
    ui->stackedWidget->setCurrentIndex(0);

    QScrollArea *scrolling = ui->ktlgScroll;

    QWidget *scrollCont = new QWidget();
    QGridLayout *scrollingLayout = new QGridLayout();

    for(int i = 0; i < Guitars.size(); i++){
        if(Guitars[i].name != " "){
            //Добавляем нужный шрифт
            const QFont font = QFont("Segoe UI Black",14,10,false);
            const QFont fontitalic = QFont("Segoe UI Black", 14, 10,true);
            //Добавляю изображение, переменная path это путь только в qsring, дальше операции с пиксмапами что бы задать изображение
             QLabel *image = new QLabel();
             QString path = QString::fromUtf8(Guitars[i].img_path.c_str());
             QPixmap startImg("Images\\" + path);
             QPixmap finalImg =  startImg.scaled(100, 100);
             image->setPixmap(finalImg);

             //задаем имя
             QLabel *name = new QLabel();
             QString qName = QString::fromUtf8(Guitars[i].name.c_str());
             name->setFont(font);
             name->setText(qName);

             //задаем стоимость
             QLabel *price = new QLabel();
             QString qPrice = QString::number(Guitars[i].price);
             price->setFont(fontitalic);
             price->setText(qPrice + "$");

             //создаем кноп очку
             QPushButton *btn = new QPushButton(this);
             btn->setFont(font);
             btn->setText("Go");
             btn->setCursor(Qt::PointingHandCursor);

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
    for(int i = 0; i < Guitars.size(); i++){
        QString buttonNum = QString::number(i);
        QPushButton *button = findChild<QPushButton*>("button" + buttonNum);
        if(button!=nullptr){
            //это нужно что бы в слоте получать номер гитары на которую нажали
            button->setProperty("index", i);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

    scrollCont->setLayout(scrollingLayout);
    scrolling->setWidget(scrollCont);
    scrolling->show();
}

void Katalog::buttonClicked(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    guitar_index = button->property("index").toInt();
    std::vector<Instrument> Guitars = ParseGuitars();
    emit sendData(Guitars[guitar_index], userToSend);
    ui->stackedWidget->setCurrentIndex(2);
}

void Katalog::recieveData(User user)
{
    userToSend = user;
}

void Katalog::backToKatalog()
{
    ui->stackedWidget->setCurrentIndex(0);
    update();
}

Katalog::~Katalog()
{
    delete ui;
}

void Katalog::on_returnToMenuButton_clicked()
{
    emit backToMainMenu();
}



