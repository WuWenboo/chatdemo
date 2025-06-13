#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTimer>

namespace Ui {
class ChatView;
}

class ChatView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatView(QWidget *parent = Q_NULLPTR);
    ~ChatView();
    void appendChatItem(QWidget *item);     //尾插
    void prependChatItem(QWidget *item);    //头插
    void insertChatItem(QWidget *before, QWidget *item);    //中间插
    void removeAllItem();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void initStyleSheet();
    Ui::ChatView *ui;
    QVBoxLayout *m_PVl;
    QScrollArea *m_pScrollArea;
    bool isAppended;

private slots:
    void onVScrollBarMoved(int min, int max);

};

#endif // CHATVIEW_H
