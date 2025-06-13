#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpmgr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  新建一个登录页面， 并将其设置为MainWindow的中心部件
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login_dialog);
    //创建和注册连接
    QObject::connect(_login_dialog, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchReg);
    QObject::connect(_login_dialog, &LoginDialog::SwitchReset, this, &MainWindow::SlotSwitchReset);
    QObject::connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_chatdialog,
                     this, &MainWindow::SlotSwitchChat);

    //测试代码， 待删除
//    emit TcpMgr::GetInstance().get()->sig_switch_chatdialog();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    _reg_dialog = new RegisterDialog(this);
    _reg_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    QObject::connect(_reg_dialog, &RegisterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(_reg_dialog);
    _login_dialog->hide();
    _reg_dialog->show();
}

void MainWindow::SlotSwitchLogin()
{
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login_dialog);

    _reg_dialog->hide();
    _login_dialog->show();
    QObject::connect(_login_dialog, &LoginDialog::SwitchReset, this, &MainWindow::SlotSwitchReset);
    QObject::connect(_login_dialog, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchReg);
}

void MainWindow::SlotSwitchLogin2()
{
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login_dialog);

    _reset_dialog->hide();
    _login_dialog->show();
    QObject::connect(_login_dialog, &LoginDialog::SwitchReset, this, &MainWindow::SlotSwitchReset);
    QObject::connect(_login_dialog, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchReg);
}

void MainWindow::SlotSwitchReset()
{
    _reset_dialog = new ResetDialog(this);
    _reset_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_reset_dialog);

    _login_dialog->hide();
    _reset_dialog->show();
    QObject::connect(_reset_dialog, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);

}

void MainWindow::SlotSwitchChat(std::shared_ptr<UserInfo> user_info)
{
    _chat_dialog = new ChatDialog(user_info);
    _chat_dialog ->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_chat_dialog);
    _chat_dialog->show();
    _login_dialog->hide();
    this->setMinimumSize(QSize(1050, 900));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

