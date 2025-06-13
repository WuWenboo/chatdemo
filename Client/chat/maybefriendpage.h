#ifndef MAYBEFRIENDPAGE_H
#define MAYBEFRIENDPAGE_H

#include <QWidget>
#include <unordered_map>
#include "maybefrienditem.h"

namespace Ui {
class MaybeFriendPage;
}

class MaybeFriendPage : public QWidget
{
    Q_OBJECT

public:
    explicit MaybeFriendPage(QWidget *parent = nullptr);
    ~MaybeFriendPage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void loadMaybeList();
    Ui::MaybeFriendPage *ui;
};

#endif // MAYBEFRIENDPAGE_H
