#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>
/**
 * @brief The TimerBtn class点击获取验证码后需要让按钮显示倒计时，然后倒计时结束后再次可点击。
 */
class TimerBtn : public QPushButton
{
    Q_OBJECT
public:
    TimerBtn(QWidget* parent = Q_NULLPTR);

    ~TimerBtn();

    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QTimer *_timer;

    int _counter;
};

#endif // TIMERBTN_H
