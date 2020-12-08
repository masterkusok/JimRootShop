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
signals:
    void sendData(User user);
private slots:
    void sendUser();

private:
    Ui::mainMenu *ui;
    Katalog *ktlg;
    User current_user;
};

#endif // MAINMENU_H
