#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <QWidget>
#include "Header.h"

namespace Ui {
class UserControl;
}

class UserControl : public QWidget
{
    Q_OBJECT

public:
    explicit UserControl(QWidget *parent = nullptr);
    ~UserControl();

private:
    Ui::UserControl *ui;
private slots:
    void update();
    void CancelClicked();
    void AcceptClicked();
};

#endif // USERCONTROL_H
