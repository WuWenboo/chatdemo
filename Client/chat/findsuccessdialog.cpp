#include "findsuccessdialog.h"
#include "ui_findsuccessdialog.h"
#include <QDir>
#include <QDebug>
#include "applyfriend.h"

FindSuccessDialog::FindSuccessDialog(QWidget *parent) :
    QDialog(parent),_parent(parent),
    ui(new Ui::FindSuccessDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加");
    //隐藏对话框标题栏
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    QString pix_path = QDir::toNativeSeparators(app_path + QDir::separator() + "static" + QDir::separator() + "head_1.jpg");

    QPixmap head_pix(pix_path);
    head_pix = head_pix.scaled(ui->head_lb->size(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->head_lb->setPixmap(head_pix);
    ui->add_friend_btn->SetState("normal","hover","press");
    this->setModal(true);
}

FindSuccessDialog::~FindSuccessDialog()
{
//    qDebug() << "FindSuccessDialog Destruct";
    delete ui;
}

void FindSuccessDialog::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    ui->name_lb->setText(si->_name);
    _si = si;
}

void FindSuccessDialog::on_add_friend_btn_clicked()
{
    this->hide();
    //弹出加好友界面
    auto applyFriend = new ApplyFriend(_parent);
    applyFriend->SetSearchInfo(_si);
    applyFriend->setModal(true);
    applyFriend->show();
}
