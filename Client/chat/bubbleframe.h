#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H

#include <QFrame>
#include "global.h"
#include <QHBoxLayout>

class BubbleFrame : public QFrame
{
    Q_OBJECT
public:
    BubbleFrame(ChatRole role, QWidget *parent = Q_NULLPTR);
    void setMargin(int margin);
    void setWidget(QWidget *w);
    ~BubbleFrame();
protected:
    void paintEvent(QPaintEvent *e);//重新绘制
private:
    QHBoxLayout *m_pHLayout;
    ChatRole m_role;
    int m_margin;
};

#endif // BUBBLEFRAME_H
