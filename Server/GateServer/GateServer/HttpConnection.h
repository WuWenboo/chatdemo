#pragma once
/*****************************************************************//**
 * \file   HttpConnection.h
 * \brief  处理http连接和解析特殊字符，将数据抛给LogicSystem类处理
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;

	HttpConnection(asio::io_context& ioc);
	
	void Start();		//用来监听读写事件

	tcp::socket& GetSocket() {
		return _socket;
	}

private:
	void CheckDeadline();	//检查是否超时

	void WriteResponse();	//应答函数

	void PreParseGetParam();	//处理url

	void HandleReq();		//处理请求

	tcp::socket _socket;	
	
	beast::flat_buffer _buffer{ 8192 };		////_buffer用来接收新数据
	
	http::request<http::dynamic_body> _request;		//_request用来解析请求
	
	http::response<http::dynamic_body> _response;		//_response用来回应客户端
	
	asio::steady_timer _deadline{		//_deadline用来做定时器判断请求是否超时阈值
		_socket.get_executor(),			//_socket调度器
		std::chrono::seconds(60)
	};

	std::string _get_url;

	std::unordered_map<std::string, std::string> _get_params;
};

