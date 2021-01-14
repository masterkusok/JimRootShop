#include "editingguitar.h"
#include "ui_editingguitar.h"

editingguitar::editingguitar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editingguitar)
{
    ui->setupUi(this);
}

editingguitar::~editingguitar()
{
    delete ui;
}
