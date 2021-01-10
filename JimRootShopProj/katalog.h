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
signals:
    void backToMainMenu();

    //это что бы отправлять юзера и номер гитары в форму
    void sendData(Instrument guitar, User user);
    //это что бы передавать юзера когда возвращаешься обратно в меню
    void returnUser(User user);

public slots:
    //это что бы отправлять юзера и номер гитары в форму
    void buttonClicked();
    void backToKatalog();
    void recieveData(User user);
    //это что бы передавать юзера когда возвращаешься обратно в меню
    void on_returnToMenuButton_clicked();
private slots:
    void update();

private:
    Ui::Katalog *ui;
    GuitarPage *gtp;
    int guitar_index;

};

#endif // KATALOG_H
