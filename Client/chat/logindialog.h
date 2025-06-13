#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = Q_NULLPTR);
    ~LoginDialog();

private:
    void initHttpHandlers();
    void initHead();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void showTip(QString str, bool b_ok);
    bool checkEmailVaild();
    bool checkPasswordVaild();
    bool enableBtn(bool enabled);
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    Ui::LoginDialog *ui;
    int _uid;
    QString _token;

public slots:
    void slot_forget_pwd();

private slots:
    void on_login_btn_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int err);

signals:
    void SwitchRegister();
    void SwitchReset();
    void sig_connect_tcp(ServerInfo );
};

#endif // LOGINDIALOG_H
