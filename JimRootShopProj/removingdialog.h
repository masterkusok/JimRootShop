#ifndef REMOVINGDIALOG_H
#define REMOVINGDIALOG_H

#include <QDialog>

namespace Ui {
class RemovingDialog;
}

class RemovingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemovingDialog(QWidget *parent = nullptr);
    ~RemovingDialog();

private:
    Ui::RemovingDialog *ui;
};

#endif // REMOVINGDIALOG_H
