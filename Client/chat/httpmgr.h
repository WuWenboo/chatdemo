#ifndef HTTPMGR
#define HTTPMGR
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include "global.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

class HttpMgr : public QObject, public Singleton<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    friend class Singleton<HttpMgr>;
public:
    ~HttpMgr();

    /**
     * @brief PostHttpReq   发送http的post请求
     * @param url           请求的url
     * @param json          请求的数据(json或者protobuf序列化)
     * @param req_id        请求的id
     * @param mod           哪个模块发出的请求mod
     */
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    HttpMgr();  //单例不能公有
    QNetworkAccessManager _manager;
    friend class Singleton<HttpMgr>;    //父类访问子类的够着函数

public slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    /**
     * @brief sig_http_finish
     * @param id                请求的id
     * @param res               处理的结果
     * @param err               错误码
     * @param mod               哪个模块
     */
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR
