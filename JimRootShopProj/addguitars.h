#ifndef ADDGUITARS_H
#define ADDGUITARS_H

#include <QWidget>
#include "Header.h"

namespace Ui {
class addguitars;
}

class addguitars : public QWidget
{
    Q_OBJECT

public:
    explicit addguitars(QWidget *parent = nullptr);
    ~addguitars();
signals:
    void goBack();
private slots:
    void on_addGuitarButton_clicked();

    void on_changeImage_clicked();

    void on_goBack_clicked();

private:
    Ui::addguitars *ui;
};

#endif // ADDGUITARS_H
