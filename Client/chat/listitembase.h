#ifndef LISTITEMBASE_H
#define LISTITEMBASE_H
#include <QWidget>
#include "global.h"

class ListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ListItemBase(QWidget *parent = Q_NULLPTR);
    void SetItemType(ListItemType itemType);
    ListItemType GetItemType();
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    ListItemType _itemType;
};

#endif // LISTITEMBASE_H
