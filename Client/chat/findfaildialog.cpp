#include "findfaildialog.h"
#include "ui_findfaildialog.h"
#include <QDebug>

FindFailDialog::FindFailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindFailDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加");
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("FindFailDlg");
    ui->fail_sure_btn->SetState("normal", "hover", "press");
    this->setModal(true);
}

FindFailDialog::~FindFailDialog()
{
//    qDebug() << "FindFailDialog destruct";
    delete ui;
}

void FindFailDialog::on_fail_sure_btn_clicked()
{
    this->hide();
}
