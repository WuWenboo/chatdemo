#pragma once
/*****************************************************************//**
 * \file   VerifyGrpcClient.h
 * \brief  通过连接池管理 gRPC 验证连接，提高效率，减少创建和销毁连接的开销。
 *
 * \author 86187
 * \date   March 2025
 *********************************************************************/

#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include "ConfigMgr.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

/**
 * @brief 连接池类 RPConPool
 */
class RPConPool {
public:
    RPConPool(size_t poolSize, std::string host, std::string port);
    ~RPConPool();

    std::unique_ptr<VerifyService::Stub> getConnection();
    void returnConnection(std::unique_ptr<VerifyService::Stub> context);
    void Close();

private:
    std::atomic<bool> b_stop_;
    std::size_t poolSize_;
    std::string host_;
    std::string port_;
    std::queue<std::unique_ptr<VerifyService::Stub>> connections_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

/**
 * @brief VerifyGrpcClient 单例类
 */
class VerifyGrpcClient : public Singleton<VerifyGrpcClient>
{
    friend class Singleton<VerifyGrpcClient>;

public:
    GetVerifyRsp GetVarifyCode(std::string email);

private:
    VerifyGrpcClient();		// Singleton

    std::unique_ptr<RPConPool> pool_;
};
