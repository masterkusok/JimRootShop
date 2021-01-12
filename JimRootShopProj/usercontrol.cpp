#include "usercontrol.h"
#include "ui_usercontrol.h"

UserControl::UserControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserControl)
{
    ui->setupUi(this);
}

UserControl::~UserControl()
{
    delete ui;
}
