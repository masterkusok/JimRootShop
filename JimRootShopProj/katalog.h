#ifndef KATALOG_H
#define KATALOG_H

#include <QWidget>
#include "Header.h"
namespace Ui {
class Katalog;
}

class Katalog : public QWidget
{
    Q_OBJECT

public:
    explicit Katalog(QWidget *parent = nullptr);
    ~Katalog();

private:
    Ui::Katalog *ui;
};

#endif // KATALOG_H
