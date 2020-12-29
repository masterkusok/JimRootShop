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
    void recieveData(User user, int guitar);

private slots:
    void on_returnButton_clicked();
signals:
    void returnToKatalog();
private:
    Ui::GuitarPage *ui;
};

#endif // GUITARPAGE_H
