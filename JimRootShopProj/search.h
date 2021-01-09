#ifndef SEARCH_H
#define SEARCH_H
#include "Header.h"
#include <QWidget>
#include "guitarpage.h"
namespace Ui {
class Search;
}

class Search : public QWidget
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();
signals:
    void sendData(Instrument guitar);
    void returnToMenu();
private slots:
    void buttonClicked();
    void returnToSearch();
    void on_applyBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::Search *ui;
    std::vector <Instrument> current_searched_guitars;
    GuitarPage *gtp = new GuitarPage;
};

#endif // SEARCH_H
