#ifndef FINDSUCCESSDIALOG_H
#define FINDSUCCESSDIALOG_H

#include <QDialog>
#include <memory>
#include "userdata.h"

namespace Ui {
class FindSuccessDialog;
}

class FindSuccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindSuccessDialog(QWidget *parent = Q_NULLPTR);
    ~FindSuccessDialog();
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);

private slots:
    void on_add_friend_btn_clicked();

private:
    Ui::FindSuccessDialog *ui;
    QWidget * _parent;
    std::shared_ptr<SearchInfo> _si;    //缓存用户信息
};

#endif // FINDSUCCESSDIALOG_H
