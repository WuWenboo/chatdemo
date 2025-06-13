#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
#include "resetdialog.h"
#include "chatdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
    void SlotSwitchLogin2();
    void SlotSwitchReset();
    void SlotSwitchChat(std::shared_ptr<UserInfo> user_info);
private:
    Ui::MainWindow *ui;
    LoginDialog *_login_dialog;
    RegisterDialog *_reg_dialog;
    ResetDialog *_reset_dialog;
    ChatDialog *_chat_dialog;
};
#endif // MAINWINDOW_H
