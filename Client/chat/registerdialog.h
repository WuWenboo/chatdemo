#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = Q_NULLPTR);
    ~RegisterDialog();
    void showTip(QString str, bool is_ok);

public slots:
    void on_get_code_btn_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

private slots:
    void on_sure_btn_clicked();

    void on_return_btn_clicked();

    void on_cancel_btn_clicked();

signals:
    void sigSwitchLogin();

private:
    void AddTipErr(TipErr tiperr, QString tips);
    void DelTipErr(TipErr tiperr);
    bool checkUserValid();
    bool checkEmailVaild();
    bool checkPasswordValid();
    bool checkConfirmValid();
    bool checkVerifyValid();
    Ui::RegisterDialog *ui;
    void initHttpHandlers();
    void ChangeTipPage();
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;
    QTimer *_countdown_timer;   //计时器
    int _countdown;             //倒计时数字
};

#endif // REGISTERDIALOG_H
