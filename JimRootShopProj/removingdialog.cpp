#include "removingdialog.h"
#include "ui_removingdialog.h"

RemovingDialog::RemovingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemovingDialog)
{
    ui->setupUi(this);
}

RemovingDialog::~RemovingDialog()
{
    delete ui;
}
