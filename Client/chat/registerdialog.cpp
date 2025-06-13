#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog), _countdown(5)
{
    ui->setupUi(this);
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
    this->initHttpHandlers();
    QObject::connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
                    this, &RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();

    ui->err_tip->clear();
    // 检查
    QObject::connect(ui->user_edit, &QLineEdit::editingFinished, this, [this](){
        checkUserValid();
    });
    QObject::connect(ui->email_edit, &QLineEdit::editingFinished, this, [this](){
        checkEmailVaild();
    });
    QObject::connect(ui->pwd_edit, &QLineEdit::editingFinished, this, [this](){
        checkPasswordValid();
    });
    QObject::connect(ui->confirm_edit, &QLineEdit::editingFinished, this, [this](){
        checkConfirmValid();
    });
    QObject::connect(ui->varify_edit, &QLineEdit::editingFinished, this, [this](){
        checkVerifyValid();
    });
    //设置浮动显示手形状
    ui->pwd_visible->setCursor(Qt::PointingHandCursor);
    ui->confirm_visible->setCursor(Qt::PointingHandCursor);

    ui->pwd_visible->SetState("unvisible","unvisible_hover","","visible",
                                "visible_hover","");

    ui->confirm_visible->SetState("unvisible","unvisible_hover","","visible",
                                    "visible_hover","");

    QObject::connect(ui->pwd_visible, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->pwd_visible->GetCurState();
        if(state == ClickLabelState::Normal){
            ui->pwd_edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->pwd_edit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "Label was clicked!";
    });

    QObject::connect(ui->confirm_visible, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->confirm_visible->GetCurState();
        if(state == ClickLabelState::Normal){
            ui->confirm_edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->confirm_edit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "Label was clicked!";
    });

    //创建定时器
    _countdown_timer = new QTimer(this);

    QObject::connect(_countdown_timer, &QTimer::timeout, [this](){
        if (_countdown == 0) {
            _countdown_timer->stop();
            emit sigSwitchLogin();
            return;
        }
        _countdown--;
        auto str = QString("注册成功，%1 s后返回登录").arg(_countdown);
        ui->tip_label->setText(str);
    });
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTip(QString str, bool is_ok)
{
    if(is_ok){
        ui->err_tip->setText(str);
        ui->err_tip->setProperty("state", "normal");
    }else{
        ui->err_tip->setText(str);
        ui->err_tip->setProperty("state", "err");
    }

    repolish(ui->err_tip);
}

void RegisterDialog::on_get_code_btn_clicked()
{
    auto email = ui->email_edit->text();
    //邮箱地址验证的正则表达式
    QRegularExpression regex(R"((\w+)(\.\_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if (match){
        //发送http验证啊
        QJsonObject json_obj;
        json_obj["email"] = email;
        //wwb00027@gmail.com
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_verifycode"),
                             json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);

    }else{
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"), false);
        return ;
    }

    // 解析 JSON 字符串， res需转化为 QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    // Json解析错误
    if (jsonDoc.isNull()){
        showTip(tr("Json解析错误"), false);
        return;
    }
    if (!jsonDoc.isObject()){
        showTip(tr("Json解析错误"), false);
        return;
    }

    QJsonObject jsonobj = jsonDoc.object();

    //调用相应的逻辑, 根据id回调
    _handlers[id](jsonDoc.object());
    return ;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        qDebug() << "Received JSON: " << jsonObj;

        if (error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"), false);
            return ;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，请注意查收"), true);
        qDebug() << "email is " << email;
    });

    //注册用户回包逻辑
    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        qDebug() << "Received JSON: " << jsonObj;
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        qDebug() << "user uuid is " << jsonObj["uuid"].toString();
        qDebug() << "email is " << email ;
        ChangeTipPage();
    });
}

void RegisterDialog::ChangeTipPage()
{
    _countdown_timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    // 启动定时器， 设置间隔为1000ms(1s)
    _countdown_timer->start(1000);
}

void RegisterDialog::on_sure_btn_clicked()
{
    if(ui->user_edit->text() == ""){
           showTip(tr("用户名不能为空"), false);
           return;
       }

       if(ui->email_edit->text() == ""){
           showTip(tr("邮箱不能为空"), false);
           return;
       }

       if(ui->pwd_edit->text() == ""){
           showTip(tr("密码不能为空"), false);
           return;
       }

       if(ui->confirm_edit->text() == ""){
           showTip(tr("确认密码不能为空"), false);
           return;
       }

       if(ui->confirm_edit->text() != ui->pwd_edit->text()){
           showTip(tr("密码和确认密码不匹配"), false);
           return;
       }

       if(ui->varify_edit->text() == ""){
           showTip(tr("验证码不能为空"), false);
           return;
       }

       //发送http请求注册用户
       QJsonObject json_obj;
       json_obj["user"] = ui->user_edit->text();
       json_obj["email"] = ui->email_edit->text();
       json_obj["password"] = xorString(ui->pwd_edit->text());
       json_obj["confirm"] = xorString(ui->confirm_edit->text());
       json_obj["verifycode"] = ui->varify_edit->text();
       HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                           json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}

void RegisterDialog::AddTipErr(TipErr tiperr, QString tips)
{
    _tip_errs[tiperr] = tips;
    showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr tiperr)
{
    _tip_errs.remove(tiperr);
    if (_tip_errs.empty()) {
        ui->err_tip->clear();
        return ;
    }
    showTip(_tip_errs.first(), false);
}

bool RegisterDialog::checkUserValid()
{
    if (ui->user_edit->text() == "") {
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailVaild()
{
   //验证邮箱的地址正则表达式
   auto email = ui->email_edit->text();
   // 邮箱地址的正则表达式
   QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
   bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
   if(!match){
       //提示邮箱不正确
       AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
       return false;
   }

   DelTipErr(TipErr::TIP_EMAIL_ERR);
   return true;
}

bool RegisterDialog::checkPasswordValid()
{
    auto pass = ui->pwd_edit->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);

    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    auto pass = ui->pwd_edit->text();
    auto confirm = ui->confirm_edit->text();

    if(confirm.length() < 6 || confirm.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(confirm).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_CONFIRM_ERR);

    if (pass != confirm) {
        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("确认密码和密码不匹配"));
        return false;
    }else{
        DelTipErr(TipErr::TIP_PWD_CONFIRM);
    }

    return true;
}

bool RegisterDialog::checkVerifyValid()
{
    auto pass = ui->varify_edit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}



void RegisterDialog::on_return_btn_clicked()
{
    _countdown_timer->stop();
    emit sigSwitchLogin();
}

void RegisterDialog::on_cancel_btn_clicked()
{
    _countdown_timer->stop();
    emit sigSwitchLogin();
}
