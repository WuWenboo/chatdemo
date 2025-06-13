#ifndef MAYBEFRIENDITEM_H
#define MAYBEFRIENDITEM_H

#include <QWidget>
#include "listitembase.h"
#include "userdata.h"
#include <memory>

namespace Ui {
class maybefriendItem;
}

class maybefriendItem : public ListItemBase
{
    Q_OBJECT

public:
    explicit maybefriendItem(QWidget *parent = nullptr);
    ~maybefriendItem();
    void SetInfo(std::shared_ptr<MaybeInfo> maybe_info);
    QSize sizeHint() const override {
        return QSize(250, 80);      //返回自定义的尺寸
    }
    int GetUid();
private:
    Ui::maybefriendItem *ui;
    std::shared_ptr<MaybeInfo> _maybe_info;
};

#endif // MAYBEFRIENDITEM_H
