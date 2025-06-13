#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include "statewidget.h"
#include "userdata.h"
#include <QListWidgetItem>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(std::shared_ptr<UserInfo> user_info, QWidget *parent = Q_NULLPTR);
    ~ChatDialog();
    void addChatUserList();
    void ClearLabelState(StateWidget* lb);
    void SetSelectChatItem(int uid = 0);
    void SetSelectChatPage(int uid = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void handleGlobalMousePress(QMouseEvent *event);

private:
    void ShowSearch(bool bsearch = false);  //默认不显示搜索
    void AddLBGroup(StateWidget* lb);
    void loadMoreChatUser();
    void loadMoreConUser(); //contact
    void UpdateChatMsg(std::vector<std::shared_ptr<TextChatData> > msgdata);
    Ui::ChatDialog *ui;
    ChatUIMode _mode;   //切换模式
    ChatUIMode _state;  //当前状态
    bool _b_loading;    //是否正在加载
    QList<StateWidget*> _lb_list;
    QMap<int, QListWidgetItem*> _chat_items_added;
    int _cur_chat_uid;  //正在聊天的对象
    QWidget *_last_widget;  //最近的widget
private slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_loading_contact_user();
//    void slot_text_changed(const QString& str);//已经合并到构造函数的lambda里，不需要了
public slots:
    void slot_apply_friend(std::shared_ptr<AddFriendApply> apply);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info);
    void slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp);
    void slot_jump_chat_item(std::shared_ptr<SearchInfo> si);
    void slot_friend_info_page(std::shared_ptr<UserInfo> user_info);
    void slot_switch_apply_friend_page();
    void slot_switch_maybe_friend_page();
    void slot_jump_chat_item_from_infopage(std::shared_ptr<UserInfo> user_info);
    void slot_item_clicked(QListWidgetItem* item);
    void slot_append_send_chat_msg(std::shared_ptr<TextChatData> msgdata);
    void slot_text_chat_msg(std::shared_ptr<TextChatMsg> msg);
};

#endif // CHATDIALOG_H
