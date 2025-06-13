#ifndef CLICKEDONCELABEL_H
#define CLICKEDONCELABEL_H
#include <QLabel>
#include <QMouseEvent>

class ClickedOnceLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedOnceLabel(QWidget *parent = Q_NULLPTR);
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
signals:
    void clicked(QString str);
};

#endif // CLICKEDONCELABEL_H
