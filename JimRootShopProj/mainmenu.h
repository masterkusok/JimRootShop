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

    void goToKatalog();

    void goToSearch();

    void goBack();

    void goToUserControl();

private slots:
    void sendUser();
    void on_KatalogBtn_clicked();

    void on_SearchBtn_clicked();

    void on_ExitBtn_clicked();

    void on_User_ControlBtn_clicked();

private:
    Ui::mainMenu *ui;
    Katalog *ktlg;
    Search *srch;
    User current_user;
};

#endif // MAINMENU_H
