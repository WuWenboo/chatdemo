#include "maybefrienditem.h"
#include "ui_maybefrienditem.h"

maybefriendItem::maybefriendItem(QWidget *parent) :
    ListItemBase(parent),
    ui(new Ui::maybefriendItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::MAYBE_FRIEND_ITEM);
}

maybefriendItem::~maybefriendItem()
{
    delete ui;
}

void maybefriendItem::SetInfo(std::shared_ptr<MaybeInfo> maybe_info)
{
    // 加载图片
    QPixmap pixmap(maybe_info->_icon);

    // 设置图片自动缩放
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);

    ui->user_name_lb->setText(maybe_info->_name);
    ui->user_chat_lb->setText(maybe_info->_desc);
    ui->recommend_lb->setText(tr("推荐添加，推荐指数：") + QString::number(maybe_info->_score, 'f', 4));
    qDebug() << maybe_info->_score;
}

int maybefriendItem::GetUid()
{
    return _maybe_info->_uid;
}
