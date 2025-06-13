#pragma once
/*****************************************************************//**
 * \file   const.h
 * \brief  全局文件
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include "Singleton.h"
#include <functional>
#include <map>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <hiredis.h>
#include <cassert>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,		//Json解析错误
	RPCFailed = 1002,		//RPC请求错误
	VerifyExpired = 1003,	//验证码过期
	VerifyCodeErr = 1004,	//验证码错误
	UserExist = 1005,		//用户已存在
	PasswordErr = 1006,		//密码错误
	EmailNotMatch = 1007,	//邮箱不匹配
	PasswordUpFailed = 1008,//更新密码失败
	PasswordInvaild = 1009,	//密码更新失败
	RPCGetFailed = 1010,	//获取rpc错误
};

#define CODEPREFIX "code_"

class Defer {
public:
	//接收一个lambda表达式或函数指针
	Defer(std::function<void()> func) : func_(func) {}

	// 析构函数中执行传入的函数
	~Defer() {
		func_();
	}
private:
	std::function<void()> func_;
};
