#include "katalog.h"
#include "ui_katalog.h"
#include <QApplication>
#include <QPushButton>
#include <QLayout>
Katalog::Katalog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Katalog)
{
    ui->setupUi(this);
    ui->scrollAreaKatalog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

Katalog::~Katalog()
{
    delete ui;
}
