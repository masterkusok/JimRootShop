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
    connect(rmv, SIGNAL(accepted()), this, SLOT(removeGuitar()));

}
GuitarPage::~GuitarPage()
{
    delete ui;
}
void GuitarPage::recieveData(Instrument guitar, User user){
    std::cout << user.role;
    if(user.role != 1){
        ui->removBtn->hide();
    }
    else{
        ui->removBtn->show();
    }
    current_guitar = guitar;
    //это все ради картинки
    QString path = QString::fromUtf8(guitar.img_path.c_str());
    QPixmap startImg("Images\\" + path);
    QPixmap finalImg =  startImg.scaled(500, 500);
    ui->imgLabel->setPixmap(finalImg);

    //это для названия прайса и материалов
    QString nameText = QString::fromUtf8(guitar.name.c_str());
    nameText+="\n";
    nameText+=QString::number(guitar.price) + "$";
    nameText+="\n";
    nameText+=QString::fromUtf8(guitar.material.c_str());
    ui->nameLabel->setText(nameText);

    // а это для описания
    QString descriptionText = QString::fromUtf8(guitar.descritp.c_str());
    ui->descriptionLabel->setText(descriptionText);
}

void GuitarPage::on_returnButton_clicked()
{    
    emit returnToKatalog();
}

void GuitarPage::removeGuitar()
{
    DeleteGuitar(current_guitar);
    emit returnToKatalog();
}


void GuitarPage::on_removBtn_clicked()
{
    rmv->show();
}
