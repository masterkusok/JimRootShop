#include "guitarpage.h"
#include "ui_guitarpage.h"
#include <string>
GuitarPage::GuitarPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuitarPage)
{
    ui->setupUi(this);
    //тут я храню номер, но это пока что рабочий костыль, забей
    int number = 0;

    Instrument Guitars[30];
    ParseGuitars(Guitars);

    QString path = QString::fromUtf8(Guitars[number].img_path.c_str());

    QPixmap startImg("Images\\" + path);
    QPixmap finalImg =  startImg.scaled(500, 500);
    ui->imgLabel->setPixmap(finalImg);


    QString nameText = QString::fromUtf8(Guitars[number].name.c_str());
    nameText+="\n";
    nameText+=QString::number(Guitars[number].price) + "$";
    nameText+="\n";
    nameText+=QString::fromUtf8(Guitars[number].material.c_str());

    ui->nameLabel->setText(nameText);

}
GuitarPage::~GuitarPage()
{
    delete ui;
}
