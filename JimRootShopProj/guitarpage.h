#ifndef GUITARPAGE_H
#define GUITARPAGE_H

#include <QWidget>
#include "Header.h"
#include "removingdialog.h"
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
    void recieveData(Instrument guitar, User user);

private slots:
    void on_returnButton_clicked();
    void removeGuitar();
    void on_removBtn_clicked();

signals:
    void returnToKatalog();
private:
    RemovingDialog *rmv = new RemovingDialog;
    Ui::GuitarPage *ui;
    Instrument current_guitar;
};

#endif // GUITARPAGE_H
