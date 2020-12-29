#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "katalog.h"
#include "search.h"

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
signals:
    void sendData(User user);
private slots:
    void backToMenu();
    void sendUser();
    void on_KatalogBtn_clicked();

private:
    Ui::mainMenu *ui;
    Katalog *ktlg;
    Search *srch;
    User current_user;
};

#endif // MAINMENU_H
