#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Header.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginConfirm_clicked();

    void on_regConfirm_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
