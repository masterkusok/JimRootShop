#include "guitarpage.h"
#include "ui_guitarpage.h"
#include <string>
#include <QTextCodec>
#include "katalog.h"
GuitarPage::GuitarPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuitarPage)
{

    ui->setupUi(this);

}
GuitarPage::~GuitarPage()
{
    delete ui;
}
void GuitarPage::recieveData(User user, int guitar){

    int number = guitar;

    Instrument Guitars[30];
    ParseGuitars(Guitars);
    //это все ради картинки
    QString path = QString::fromUtf8(Guitars[number].img_path.c_str());
    QPixmap startImg("Images\\" + path);
    QPixmap finalImg =  startImg.scaled(500, 500);
    ui->imgLabel->setPixmap(finalImg);

    //это для названия прайса и материалов
    QString nameText = QString::fromUtf8(Guitars[number].name.c_str());
    nameText+="\n";
    nameText+=QString::number(Guitars[number].price) + "$";
    nameText+="\n";
    nameText+=QString::fromUtf8(Guitars[number].material.c_str());
    ui->nameLabel->setText(nameText);

    // а это для описания
    QString descriptionText = QString::fromUtf8(Guitars[number].descritp.c_str());
    ui->descriptionLabel->setText(descriptionText);
}

void GuitarPage::on_returnButton_clicked()
{
    Katalog *ktlg = new Katalog();
    ktlg->show();
    this->close();
}
