#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Header.h"
#include "mainmenu.h"
#include "katalog.h"
#include "search.h"
#include "guitarpage.h"
#include "usercontrol.h"
#include "addguitars.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sendData(User user);
    void addgiSendData(int openCode, Instrument guitar);
private slots:
    void showMenu();
    void showKatalog();
    void on_loginConfirm_clicked();
    void onLoginSend();
    void on_regConfirm_clicked();
    void showSearch();
    void showMainWindow();
    void showUserControl();
    void showAddGuitar();

private:
    Ui::MainWindow *ui;
    mainMenu *MainMenu;
    Katalog *ktlg;
    Search *srch;
    GuitarPage *gtp;
    UserControl *cntrl;
    addguitars *addgi;
};
#endif // MAINWINDOW_H
