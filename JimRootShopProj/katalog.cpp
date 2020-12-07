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
             QPushButton *btn = new QPushButton(this);
             btn->setText("перейти");

             QString buttonNum = QString::number(i);
             btn->setObjectName("button" + buttonNum);
             scrollingLayout->addWidget(image, i, 1);
             scrollingLayout->addWidget(name, i, 2);
             scrollingLayout->addWidget(price, i, 3);
             scrollingLayout->addWidget(btn, i, 4);
        }
    }
    for(int i = 0; i < number; i++){
        QString buttonNum = QString::number(i);
        QPushButton *button = findChild<QPushButton*>("button" + buttonNum);
        if(button!=nullptr){
            button->setProperty("index", i);
            QObject::connect(button, SIGNAL(clicked()), this,  SLOT(buttonClicked()));
        }
    }

    scrollCont->setLayout(scrollingLayout);
    scrolling->setWidget(scrollCont);
    scrolling->setGeometry(110, 140, 751, 381);
    scrolling->show();
    GuitarPage *gtp = new GuitarPage();

}

void Katalog::buttonClicked(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    guitar_index = button->property("index").toInt();
    GuitarPage currentGuitar;
    User user;
    this->hide();
    gtp.show();
}

Katalog::~Katalog()
{
    delete ui;
}
