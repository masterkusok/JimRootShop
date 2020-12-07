#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "katalog.h"
namespace Ui {
class mainMenu;
}

class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();
public slots:
    void recieveData(User user);
private slots:
    void on_KatalogBtn_clicked();

private:
    Ui::mainMenu *ui;
};

#endif // MAINMENU_H
