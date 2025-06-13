#include "timerbtn.h"
#include <QMouseEvent>
#include <QDebug>

TimerBtn::TimerBtn(QWidget *parent)
    : QPushButton(parent), _counter(10)
{
    _timer = new QTimer(this);

    QObject::connect(_timer, &QTimer::timeout, [this](){
        _counter--;
        if (_counter <= 0) {
            _timer->stop();
            _counter = 10;
            this->setText("获取");
            this->setEnabled(true);
            return ;
        }
        this->setText(QString::number(_counter));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {    //处理鼠标左键事务
        qDebug() << "MyButton was released!";
        this->setEnabled(false);
        this->setText(QString::number(_counter));
        _timer->start(1000);
        emit clicked();
    }
    //调用基类以确保正常的事件处理逻辑
    QPushButton::mouseReleaseEvent(e);
}
