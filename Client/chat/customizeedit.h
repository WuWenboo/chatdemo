#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H
#include <QLineEdit>
#include <QDebug>

class CustomizeEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget *parent = Q_NULLPTR);
    void SetMaxLength(int maxLen);
protected:
    void focusOutEvent(QFocusEvent *event) override;    //失去焦点
private:
    void limitTextLength(QString text);

    int _max_len;
signals:
    void sig_foucus_out();
};

#endif // CUSTOMIZEEDIT_H
