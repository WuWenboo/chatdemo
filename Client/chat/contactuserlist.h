#ifndef CONTACTUSERLIST_H
#define CONTACTUSERLIST_H

#include <QListWidget>
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QDebug>
#include <memory>
#include "userdata.h"

class ConUserItem;

class ContactUserList : public QListWidget
{
    Q_OBJECT
public:
    ContactUserList(QWidget *parent = Q_NULLPTR);
    void ShowRedPoint(bool bshow = true);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override ;

private:
    void addContactUserList();

public slots:
     void slot_item_clicked(QListWidgetItem *item);
     void slot_add_auth_firend(std::shared_ptr<AuthInfo>);
     void slot_auth_rsp(std::shared_ptr<AuthRsp>);
signals:
    void sig_loading_contact_user();
    void sig_switch_apply_friend_page();
    void sig_switch_friend_info_page(std::shared_ptr<UserInfo> user_info);
    void sig_switch_maybe_friend_page();
private:
    ConUserItem* _add_friend_item;
    ConUserItem* _con_maybe_friend_item;
    QListWidgetItem * _groupitem;
    bool _load_pending;
};

#endif // CONTACTUSERLIST_H
