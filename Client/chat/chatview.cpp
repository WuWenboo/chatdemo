#include "chatview.h"
#include "ui_chatview.h"
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>

ChatView::ChatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatView), isAppended(false)
{
    ui->setupUi(this);
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->setMargin(0);

    m_pScrollArea = new QScrollArea();
    m_pScrollArea->setObjectName("chat_area");  //便于写Qss
    pMainLayout->addWidget(m_pScrollArea);

    QWidget *wid = new QWidget(this);
    wid->setObjectName("chat_bg");
    wid->setAutoFillBackground(true);       //设置小部件自动填充颜色

    QVBoxLayout *pVLayout_1 = new QVBoxLayout();
    pVLayout_1->addWidget(new QWidget(), 100000);   //100000为伸缩因子，像比例大小
    wid->setLayout(pVLayout_1);
    m_pScrollArea->setWidget(wid);

    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
    QObject::connect(pVScrollBar, &QScrollBar::rangeChanged, this, &ChatView::onVScrollBarMoved);

    //把垂直ScrollBar放到上面， 而不是原来的并排
    QHBoxLayout *pHLayout_2 = new QHBoxLayout();
    pHLayout_2->addWidget(pVScrollBar, 0, Qt::AlignRight);
    pHLayout_2->setMargin(0);
    m_pScrollArea->setLayout(pHLayout_2);
    pVScrollBar->setHidden(true);

    m_pScrollArea->setWidgetResizable(true);//允许自动改变大小
    m_pScrollArea->installEventFilter(this);
    initStyleSheet();
}

ChatView::~ChatView()
{
    delete ui;
}

void ChatView::appendChatItem(QWidget *item)
{
    QVBoxLayout *vl = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());
    vl->insertWidget(vl->count()-1, item);
    isAppended = true;
}

void ChatView::prependChatItem(QWidget *item)
{

}

void ChatView::insertChatItem(QWidget *before, QWidget *item)
{

}

void ChatView::removeAllItem()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(m_pScrollArea->widget()->layout());

    int count = layout->count();

    for (int i = 0; i < count - 1; ++i) {
        QLayoutItem* item = layout->takeAt(0); // 始终从第一个控件开始删除
        if (item) {
            if (QWidget* widget = item->widget()) {
                delete widget;
            }
            delete item;
        }
    }
}

bool ChatView::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Enter && watched == m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(m_pScrollArea->verticalScrollBar()->maximum() == 0);
    }
    else if(event->type() == QEvent::Leave && watched == m_pScrollArea)
    {
         m_pScrollArea->verticalScrollBar()->setHidden(true);
    }
    return QWidget::eventFilter(watched, event);
}

void ChatView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatView::initStyleSheet()
{

}

void ChatView::onVScrollBarMoved(int min, int max)
{
    if(isAppended) //添加item可能调用多次
    {
        QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
        pVScrollBar->setSliderPosition(pVScrollBar->maximum());
        //500毫秒内可能调用多次， 休眠一会再调整
        QTimer::singleShot(500, [this]()
        {
            isAppended = false;
        });
    }
}
