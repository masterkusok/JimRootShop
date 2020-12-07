#ifndef KATALOG_H
#define KATALOG_H

#include <QWidget>
#include "Header.h"
#include "guitarpage.h"
namespace Ui {
class Katalog;
}

class Katalog : public QWidget
{
    Q_OBJECT

public:
    int btnNumber;
    explicit Katalog(QWidget *parent = nullptr);
    ~Katalog();

public slots:
    void buttonClicked();

private slots:
    void on_returnToMenuButton_clicked();

private:
    Ui::Katalog *ui;
    GuitarPage gtp;
    int guitar_index;
    User current_user;
};

#endif // KATALOG_H
