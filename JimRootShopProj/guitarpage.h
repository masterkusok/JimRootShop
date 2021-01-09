#ifndef GUITARPAGE_H
#define GUITARPAGE_H

#include <QWidget>
#include "Header.h"

namespace Ui {
class GuitarPage;
}

class GuitarPage : public QWidget
{
    Q_OBJECT
public:
    explicit GuitarPage(QWidget *parent = nullptr);
    ~GuitarPage();
public slots:
    void recieveData(Instrument guitar);

private slots:
    void on_returnButton_clicked();

    void on_removBtn_clicked();

signals:
    void returnToKatalog();
private:
    Ui::GuitarPage *ui;
    Instrument current_guitar;
};

#endif // GUITARPAGE_H
