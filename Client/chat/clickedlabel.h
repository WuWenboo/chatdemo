#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H
#include <QLabel>
#include "global.h"

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent = Q_NULLPTR);
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
//    一个Label有六种状态，普通状态，普通的悬浮状态，普通的点击状态，选中状态，选中的悬浮状态，选中的点击状态。
    void SetState(QString normal = "", QString hover="", QString press="",
                  QString select = "", QString select_hover = "", QString select_press= "");
    ClickLabelState GetCurState();
    bool SetCurState(ClickLabelState state);
    void ResetNormalState();

private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;
    QString _selected;
    QString _selected_hover;
    QString _selected_press;
    ClickLabelState _curstate;

signals:
    void clicked(QString, ClickLabelState);
};

#endif // CLICKEDLABEL_H
