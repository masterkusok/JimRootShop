#ifndef EDITINGGUITAR_H
#define EDITINGGUITAR_H

#include <QWidget>

namespace Ui {
class editingguitar;
}

class editingguitar : public QWidget
{
    Q_OBJECT

public:
    explicit editingguitar(QWidget *parent = nullptr);
    ~editingguitar();

private:
    Ui::editingguitar *ui;
};

#endif // EDITINGGUITAR_H
