#include "loadingdialog.h"
#include "ui_loadingdialog.h"
#include <QMovie>
#include <QDebug>

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground); //设置为透明色
    //获取屏幕尺寸
    setFixedSize(parent->size());   //设置对话框为全屏尺寸
//    qDebug() << "LoadingDialog Parent class name:" << this->parent()->metaObject()->className();
    QMovie *movie = new QMovie(":/res/loading.gif");    //加载动画的资源文件
    ui->loading_lb->setMovie(movie);
    movie->start();
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
