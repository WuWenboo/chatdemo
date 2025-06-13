#include "maybefriendpage.h"
#include "ui_maybefriendpage.h"
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
#include <QRandomGenerator>
#include "maybefrienditem.h"
#include "authenfriend.h"
#include "applyfriend.h"
#include "tcpmgr.h"
#include "usermgr.h"

MaybeFriendPage::MaybeFriendPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaybeFriendPage)
{
    ui->setupUi(this);
    loadMaybeList();
}

MaybeFriendPage::~MaybeFriendPage()
{
    delete ui;
}

void MaybeFriendPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MaybeFriendPage::loadMaybeList()
{
    //添加好友申请
    auto maybe_list = UserMgr::GetInstance()->GetMaybeList();
    for(auto &maybe: maybe_list){
        auto* maybe_item = new maybefriendItem();
        maybe_item->SetInfo(maybe);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(maybe_item->sizeHint());
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui->maybe_friend_list->insertItem(0,item);
        ui->maybe_friend_list->setItemWidget(item, maybe_item);
    }
}
