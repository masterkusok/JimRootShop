#include "addguitars.h"
#include "ui_addguitars.h"
#include <string>
#include <QMessageBox>
#include <QFileDialog>
QString img_path;
addguitars::addguitars(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addguitars)
{
    ui->setupUi(this);
}

addguitars::~addguitars()
{
    delete ui;
}

void addguitars::on_addGuitarButton_clicked()
{
    std::vector<Instrument> Guitars = ParseGuitars();
    QString imgPath = QString::number(Guitars.size() + 1);
    QString imgPat = imgPath + ".jpg";
    QFile::copy(img_path,"Images/" + imgPath + ".jpg");
    std::string brand = ui->brandLine->text().toStdString();
    std::string shape = ui->shapeLine->text().toStdString();
    std::string name = ui->nameLine->text().toStdString();
    std::string price = ui->spinBox->text().toStdString();
    std::string material = ui->materialLine->text().toStdString();
    QStringList descr = ui->plainTextEdit->toPlainText().split('\n');
    std::string description = "";
    for(int i = 0;i < descr.length();i++){
        description = description + descr[i].toStdString();
    }
    if(brand != "" && brand != " " &&
       shape != "" && shape != " " &&
       name != "" && name != " " &&
       price != "" && price != " " &&
       material != "" && material != " " &&
       description != "" && description != " " &&
       img_path != "" && img_path != " "){
       addGuitar(brand,shape,name,price,material,imgPat.toStdString(),description);
       QMessageBox::information(this, "Adding guitar", "Guitar added successfully");
    }
    else{
        QMessageBox::information(this, "Adding guitar","You didn't fill all the fields");
    }
}

void addguitars::on_changeImage_clicked()
{
    img_path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");
    QPixmap startImg(img_path);
    QPixmap finalImg =  startImg.scaled(300, 300);
    ui->imageLabel->setPixmap(finalImg);
}

void addguitars::on_goBack_clicked()
{
    emit goBack();
}
