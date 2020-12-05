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

    Instrument Guitars[30];
    ParseGuitars(Guitars);
    int number = getNumberOfGuitars(Guitars);



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
             QPushButton *btn = new QPushButton();
             btn->setText("перейти");

             scrollingLayout->addWidget(image, i, 1);
             scrollingLayout->addWidget(name, i, 2);
             scrollingLayout->addWidget(price, i, 3);
             scrollingLayout->addWidget(btn, i, 4);
        }
    }

    scrollCont->setLayout(scrollingLayout);
    scrolling->setWidget(scrollCont);
    scrolling->show();

}

Katalog::~Katalog()
{
    delete ui;
}
