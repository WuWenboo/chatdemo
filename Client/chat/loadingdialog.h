#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = Q_NULLPTR);
    ~LoadingDialog();

private:
    Ui::LoadingDialog *ui;
};

#endif // LOADINGDIALOG_H
