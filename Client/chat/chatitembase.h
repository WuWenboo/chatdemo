#ifndef CHATITEMBASE_H
#define CHATITEMBASE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "global.h"
/**
 * 消息显示框
 */

class BubbleFrame;

namespace Ui {
class ChatItemBase;
}

class ChatItemBase : public QWidget
{
    Q_OBJECT

public:
    ChatItemBase(ChatRole role, QWidget *parent = Q_NULLPTR);
    void setUserName(const QString& name);
    void setUserIcon(const QPixmap& icon);
    void setWidget(QWidget *w);

    ~ChatItemBase();

private:
    ChatRole m_role;
    QLabel *m_pNameLabel;
    QLabel *m_pIconLabel;
    QWidget *m_pBubble;

    Ui::ChatItemBase *ui;
};

#endif // CHATITEMBASE_H
